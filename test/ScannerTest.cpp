#include <fstream>
#include "gtest/gtest.h"

#include "../src/Scanner.hpp"
#include "../src/error.hpp"
#include "../src/errormanager.hpp"

using namespace std;

namespace Meow
{
	typedef PalParser::token token;

	class ScannerTest : public ::testing::Test
	{
		protected:

			ScannerTest() 
			{
			}

			virtual void SetUp()
			{
				m_input = NULL;
				m_errorManager = NULL;
				m_scanner = NULL;
			}

			virtual void TearDown()
			{
				if (m_input)
				{
					m_input->close();
					delete m_input;
				}

				if (m_errorManager)
				{
					delete m_errorManager;
				}

				if (m_scanner)
				{
					delete m_scanner;
				}
			}

			void initTest(const char* fileName)
			{
				m_input = new ifstream(fileName);
				EXPECT_TRUE(m_input->is_open()) << "Couldn't open test input file!";

				if (m_input->is_open())
				{
					m_errorManager = new ErrorManager();
					m_scanner = new PalScanner(m_input, m_errorManager);
				}
			}

			PalParser::semantic_type yylval;
			ErrorManager* m_errorManager;
			PalScanner* m_scanner;
			ifstream* m_input;
	};

// Using preprocessor macro gives nicer output for failed tests :)
#define EXPECT_TOKEN(token) \
	EXPECT_EQ(token, m_scanner->yylex(&yylval))

	TEST_F(ScannerTest, TestValidInput001)
	{
		initTest("test/test_cases/test001.pal");

		EXPECT_TOKEN(token::PROGRAM);
		EXPECT_TOKEN(token::IDENTIFIER);
		EXPECT_TOKEN(token::LEFT_PAREN);
		EXPECT_TOKEN(token::IDENTIFIER);
		EXPECT_TOKEN(token::COMMA);
		EXPECT_TOKEN(token::IDENTIFIER);
		EXPECT_TOKEN(token::RIGHT_PAREN);
		EXPECT_TOKEN(token::SEMICOLON);

		EXPECT_TOKEN(token::PAL_BEGIN);

		EXPECT_TOKEN(token::END);
		EXPECT_TOKEN(token::PERIOD);
	}

	TEST_F(ScannerTest, TestValidInput002)
	{
		initTest("test/test_cases/test002.pal");

		EXPECT_TOKEN(token::PROGRAM);
		EXPECT_TOKEN(token::IDENTIFIER);
		EXPECT_TOKEN(token::LEFT_PAREN);
		EXPECT_TOKEN(token::IDENTIFIER);
		EXPECT_TOKEN(token::COMMA);
		EXPECT_TOKEN(token::IDENTIFIER);
		EXPECT_TOKEN(token::RIGHT_PAREN);
		EXPECT_TOKEN(token::SEMICOLON);
		EXPECT_TOKEN(token::PAL_BEGIN);

			EXPECT_TOKEN(token::IDENTIFIER);
			EXPECT_TOKEN(token::LEFT_PAREN);
			EXPECT_TOKEN(token::STRING_LITERAL);
			EXPECT_TOKEN(token::RIGHT_PAREN);
			EXPECT_TOKEN(token::SEMICOLON);

		EXPECT_TOKEN(token::END);
		EXPECT_TOKEN(token::PERIOD);
	}

	TEST_F(ScannerTest, TestValidInput003)
	{
		initTest("test/test_cases/test003.pal");

		EXPECT_TOKEN(token::PROGRAM);
		EXPECT_TOKEN(token::IDENTIFIER);
		EXPECT_TOKEN(token::LEFT_PAREN);
		EXPECT_TOKEN(token::IDENTIFIER);
		EXPECT_TOKEN(token::COMMA);
		EXPECT_TOKEN(token::IDENTIFIER);
		EXPECT_TOKEN(token::RIGHT_PAREN);
		EXPECT_TOKEN(token::SEMICOLON);

		EXPECT_TOKEN(token::PAL_BEGIN);
		EXPECT_TOKEN(token::END);
		EXPECT_TOKEN(token::PERIOD);
	}

	TEST_F(ScannerTest, TestUnclosedComment)
	{
		initTest("test/test_cases/btestUnclosedComment.pal");

		EXPECT_TOKEN(token::PROGRAM);
		EXPECT_TOKEN(token::IDENTIFIER);
		EXPECT_TOKEN(token::LEFT_PAREN);
		EXPECT_TOKEN(token::IDENTIFIER);
		EXPECT_TOKEN(token::COMMA);
		EXPECT_TOKEN(token::IDENTIFIER);
		EXPECT_TOKEN(token::RIGHT_PAREN);
		EXPECT_TOKEN(token::SEMICOLON);

		EXPECT_TOKEN(token::PAL_BEGIN);

		// there should be an unclosed comment starting at this point
		// therefore, scanner should just return 0 next as the rest of the file
		// will be commented out.
		EXPECT_TOKEN(0);
		//EXPECT_EQ(0, scanner.yylex(&yylval));

		// should only be one error
		vector<const Error*> unclosedErrors;
		const vector<Error*> errors = m_errorManager->getErrors();

		EXPECT_EQ(1u, errors.size()); 

		// should be one and only one UnclosedComment error, on line 3
		vector<Error*>::const_iterator errorIt;
		for (errorIt = errors.begin(); errorIt != errors.end(); ++errorIt)
		{
			Error* error = *errorIt;
			if (error->getErrorCode() == UnclosedComment)
			{
				unclosedErrors.push_back(error);
			}
		}

		EXPECT_EQ(1u, unclosedErrors.size());

		if (unclosedErrors.size() > 0)
		{
			const Error* unclosedError = unclosedErrors.front();
			EXPECT_EQ(3u, unclosedError->getLineNumber());
		}
	}

	TEST_F(ScannerTest, TestUnclosedString)
	{
		initTest("test/test_cases/btestUnclosedString.pal");

		EXPECT_TOKEN(token::PROGRAM);
		EXPECT_TOKEN(token::IDENTIFIER);
		EXPECT_TOKEN(token::LEFT_PAREN);
		EXPECT_TOKEN(token::IDENTIFIER);
		EXPECT_TOKEN(token::COMMA);
		EXPECT_TOKEN(token::IDENTIFIER);
		EXPECT_TOKEN(token::RIGHT_PAREN);
		EXPECT_TOKEN(token::SEMICOLON);

		EXPECT_TOKEN(token::PAL_BEGIN);
		
		// TODO - tokenize the unclosed string or ignore it?

		// Next line should tokenize fine!
		EXPECT_TOKEN(token::IDENTIFIER);
		EXPECT_TOKEN(token::LEFT_PAREN);
		EXPECT_TOKEN(token::STRING_LITERAL);
		EXPECT_TOKEN(token::RIGHT_PAREN);
		EXPECT_TOKEN(token::SEMICOLON);

		// TODO - tokenize the unclosed string or ignore it?
		EXPECT_TOKEN(token::IDENTIFIER);
		EXPECT_TOKEN(token::LEFT_PAREN);

		// Next line should tokenize fine!
		EXPECT_TOKEN(token::IDENTIFIER);
		EXPECT_TOKEN(token::LEFT_PAREN);
		EXPECT_TOKEN(token::STRING_LITERAL);
		EXPECT_TOKEN(token::RIGHT_PAREN);
		EXPECT_TOKEN(token::SEMICOLON);

		EXPECT_TOKEN(token::END);
		EXPECT_TOKEN(token::PERIOD);

		// should be 2 errors
		const vector<Error*> errors = m_errorManager->getErrors();
		EXPECT_EQ(2u, errors.size()); 

		// should be 2 unclosed string errors
		if (errors.size() == 2)
		{
			EXPECT_EQ(UnclosedString, errors.at(0)->getErrorCode());
			EXPECT_EQ(3u, errors.at(0)->getLineNumber());
			EXPECT_EQ(UnclosedString, errors.at(1)->getErrorCode());
			EXPECT_EQ(5u, errors.at(1)->getLineNumber());
		}
	}

	TEST_F(ScannerTest, TestSubtractionWithoutSpace)
	{
		initTest("test/test_cases/subtractionWithoutSpace.pal");

		EXPECT_TOKEN(token::PROGRAM);
		EXPECT_TOKEN(token::IDENTIFIER);
		EXPECT_TOKEN(token::LEFT_PAREN);
		EXPECT_TOKEN(token::IDENTIFIER);
		EXPECT_TOKEN(token::COMMA);
		EXPECT_TOKEN(token::IDENTIFIER);
		EXPECT_TOKEN(token::RIGHT_PAREN);
		EXPECT_TOKEN(token::SEMICOLON);

		EXPECT_TOKEN(token::VAR);
		EXPECT_TOKEN(token::IDENTIFIER);
		EXPECT_TOKEN(token::COLON);
		EXPECT_TOKEN(token::IDENTIFIER);
		EXPECT_TOKEN(token::SEMICOLON);

		EXPECT_TOKEN(token::PAL_BEGIN);

		// i := i-1-2;
		EXPECT_TOKEN(token::IDENTIFIER);
		EXPECT_TOKEN(token::ASSIGN);
		EXPECT_TOKEN(token::IDENTIFIER);
		EXPECT_TOKEN(token::MINUS);
		EXPECT_TOKEN(token::INT_CONST);
		EXPECT_TOKEN(token::MINUS);
		EXPECT_TOKEN(token::INT_CONST);
		EXPECT_TOKEN(token::SEMICOLON);

		EXPECT_TOKEN(token::END);
		EXPECT_TOKEN(token::PERIOD);
	}

	TEST_F(ScannerTest, TestExpressionsWithoutSpace)
	{
		initTest("test/test_cases/expressionsWithoutSpace.pal");

		EXPECT_TOKEN(token::PROGRAM);
		EXPECT_TOKEN(token::IDENTIFIER);
		EXPECT_TOKEN(token::LEFT_PAREN);
		EXPECT_TOKEN(token::IDENTIFIER);
		EXPECT_TOKEN(token::COMMA);
		EXPECT_TOKEN(token::IDENTIFIER);
		EXPECT_TOKEN(token::RIGHT_PAREN);
		EXPECT_TOKEN(token::SEMICOLON);

		EXPECT_TOKEN(token::VAR);
		EXPECT_TOKEN(token::IDENTIFIER);
		EXPECT_TOKEN(token::COLON);
		EXPECT_TOKEN(token::IDENTIFIER);
		EXPECT_TOKEN(token::SEMICOLON);

		EXPECT_TOKEN(token::PAL_BEGIN);

		// i := i-1-2;
		EXPECT_TOKEN(token::IDENTIFIER);
		EXPECT_TOKEN(token::ASSIGN);
		EXPECT_TOKEN(token::IDENTIFIER);
		EXPECT_TOKEN(token::MINUS);
		EXPECT_TOKEN(token::INT_CONST);
		EXPECT_TOKEN(token::MINUS);
		EXPECT_TOKEN(token::INT_CONST);
		EXPECT_TOKEN(token::SEMICOLON);

		// i := i+1+2;
		EXPECT_TOKEN(token::IDENTIFIER);
		EXPECT_TOKEN(token::ASSIGN);
		EXPECT_TOKEN(token::IDENTIFIER);
		EXPECT_TOKEN(token::PLUS);
		EXPECT_TOKEN(token::INT_CONST);
		EXPECT_TOKEN(token::PLUS);
		EXPECT_TOKEN(token::INT_CONST);
		EXPECT_TOKEN(token::SEMICOLON);

		// i := (23+34*2*(20/10));
		EXPECT_TOKEN(token::IDENTIFIER);
		EXPECT_TOKEN(token::ASSIGN);
		EXPECT_TOKEN(token::LEFT_PAREN);

		EXPECT_TOKEN(token::INT_CONST);
		EXPECT_TOKEN(token::PLUS);
		EXPECT_TOKEN(token::INT_CONST);
		EXPECT_TOKEN(token::MULTIPLY);
		EXPECT_TOKEN(token::INT_CONST);
		EXPECT_TOKEN(token::MULTIPLY);

		EXPECT_TOKEN(token::LEFT_PAREN);
		EXPECT_TOKEN(token::INT_CONST);
		EXPECT_TOKEN(token::REAL_DIVIDE);
		EXPECT_TOKEN(token::INT_CONST);
		EXPECT_TOKEN(token::RIGHT_PAREN);

		EXPECT_TOKEN(token::RIGHT_PAREN);
		EXPECT_TOKEN(token::SEMICOLON);

		EXPECT_TOKEN(token::END);
		EXPECT_TOKEN(token::PERIOD);
	}
}

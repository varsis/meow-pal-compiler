#include <fstream>
#include "gtest/gtest.h"

#include "../src/Scanner.hpp"
#include "../src/Error.hpp"
#include "../src/ErrorManager.hpp"

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

	TEST_F(ScannerTest, TestValidRealConstants)
	{
		initTest("test/test_cases/btestValidRealConstants.pal");

		EXPECT_TOKEN(token::REAL_CONST);
		EXPECT_TOKEN(token::REAL_CONST);
		EXPECT_TOKEN(token::REAL_CONST);
		EXPECT_TOKEN(token::REAL_CONST);
		EXPECT_TOKEN(token::REAL_CONST);
		EXPECT_TOKEN(token::REAL_CONST);
		EXPECT_TOKEN(token::REAL_CONST);
	}

	TEST_F(ScannerTest, TestValidIntegerConstants)
	{
		initTest("test/test_cases/btestValidIntegerConstants.pal");


		EXPECT_TOKEN(token::INT_CONST);
		EXPECT_TOKEN(token::INT_CONST);
		EXPECT_TOKEN(token::INT_CONST);
		EXPECT_TOKEN(token::INT_CONST);
		EXPECT_TOKEN(token::INT_CONST);
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

		// should only be one error
		const multiset<Error*,classcomp>* errors = m_errorManager->getErrors();
		EXPECT_EQ(1u, errors->size()); 

		// should be one and only one UnclosedComment error, on line 3
		if (errors->size() == 1)
		{
			EXPECT_EQ(UnclosedComment, (*errors->begin())->getErrorCode());
			EXPECT_EQ(3u, (*errors->begin())->getLineNumber());
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
		
		// Should be invalid, but we'll still get the token
		EXPECT_TOKEN(token::STRING_LITERAL);

		// Next line should tokenize fine!
		EXPECT_TOKEN(token::IDENTIFIER);
		EXPECT_TOKEN(token::LEFT_PAREN);
		EXPECT_TOKEN(token::STRING_LITERAL);
		EXPECT_TOKEN(token::RIGHT_PAREN);
		EXPECT_TOKEN(token::SEMICOLON);

		EXPECT_TOKEN(token::IDENTIFIER);
		EXPECT_TOKEN(token::LEFT_PAREN);

		// Should be invalid, but we'll still get the token
		EXPECT_TOKEN(token::STRING_LITERAL);

		// Next line should tokenize fine!
		EXPECT_TOKEN(token::IDENTIFIER);
		EXPECT_TOKEN(token::LEFT_PAREN);
		EXPECT_TOKEN(token::STRING_LITERAL);
		EXPECT_TOKEN(token::RIGHT_PAREN);
		EXPECT_TOKEN(token::SEMICOLON);

		EXPECT_TOKEN(token::END);
		EXPECT_TOKEN(token::PERIOD);

		// should be 2 errors
		const multiset<Error*,classcomp>* errors = m_errorManager->getErrors();
		EXPECT_EQ(2u, errors->size()); 

		// should be 2 unclosed string errors
		if (errors->size() == 2)
		{
			multiset<Error*>::iterator errIt = errors->begin();

			EXPECT_EQ(UnclosedString, (*errIt)->getErrorCode());
			EXPECT_EQ(3u, (*errIt)->getLineNumber());

			++errIt;

			EXPECT_EQ(UnclosedString, (*errIt)->getErrorCode());
			EXPECT_EQ(5u, (*errIt)->getLineNumber());
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

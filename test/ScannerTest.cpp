#include <fstream>
#include "gtest/gtest.h"

#include "../src/Scanner.hpp"
#include "../src/error.hpp"
#include "../src/errormanager.hpp"

using namespace std;

namespace Meow
{
	typedef PalParser::token token;

	TEST(ScannerTest, TestValidInput001)
	{
		ifstream input("test/test_cases/test001.pal");

		EXPECT_TRUE(input.is_open()) << "Couldn't open test input file!";

		if (input.is_open())
		{
			ErrorManager errorManager;
			PalScanner scanner(&input, &errorManager);

			EXPECT_EQ(token::PROGRAM, scanner.yylex());
			EXPECT_EQ(token::IDENTIFIER, scanner.yylex());
			EXPECT_EQ(token::LEFT_PAREN, scanner.yylex());
			EXPECT_EQ(token::IDENTIFIER, scanner.yylex());
			EXPECT_EQ(token::COMMA, scanner.yylex());
			EXPECT_EQ(token::IDENTIFIER, scanner.yylex());
			EXPECT_EQ(token::RIGHT_PAREN, scanner.yylex());
			EXPECT_EQ(token::SEMICOLON, scanner.yylex());

			EXPECT_EQ(token::PAL_BEGIN, scanner.yylex());

			EXPECT_EQ(token::END, scanner.yylex());
			EXPECT_EQ(token::PERIOD, scanner.yylex());
		}

		input.close();
	}

	TEST(ScannerTest, TestValidInput002)
	{
		ifstream input("test/test_cases/test002.pal");

		EXPECT_TRUE(input.is_open()) << "Couldn't open test input file!";

		if (input.is_open())
		{
			ErrorManager errorManager;
			PalScanner scanner(&input, &errorManager);

			EXPECT_EQ(token::PROGRAM, scanner.yylex());
			EXPECT_EQ(token::IDENTIFIER, scanner.yylex());
			EXPECT_EQ(token::LEFT_PAREN, scanner.yylex());
			EXPECT_EQ(token::IDENTIFIER, scanner.yylex());
			EXPECT_EQ(token::COMMA, scanner.yylex());
			EXPECT_EQ(token::IDENTIFIER, scanner.yylex());
			EXPECT_EQ(token::RIGHT_PAREN, scanner.yylex());
			EXPECT_EQ(token::SEMICOLON, scanner.yylex());

			EXPECT_EQ(token::PAL_BEGIN, scanner.yylex());

				EXPECT_EQ(token::IDENTIFIER, scanner.yylex());
				EXPECT_EQ(token::LEFT_PAREN, scanner.yylex());
				EXPECT_EQ(token::STRING_LITERAL, scanner.yylex());
				EXPECT_EQ(token::RIGHT_PAREN, scanner.yylex());
				EXPECT_EQ(token::SEMICOLON, scanner.yylex());

			EXPECT_EQ(token::END, scanner.yylex());
			EXPECT_EQ(token::PERIOD, scanner.yylex());
		}

		input.close();
	}

	TEST(ScannerTest, TestValidInput003)
	{
		ifstream input("test/test_cases/test003.pal");

		EXPECT_TRUE(input.is_open()) << "Couldn't open test input file!";

		if (input.is_open())
		{
			ErrorManager errorManager;
			PalScanner scanner(&input, &errorManager);

			EXPECT_EQ(token::PROGRAM, scanner.yylex());
			EXPECT_EQ(token::IDENTIFIER, scanner.yylex());
			EXPECT_EQ(token::LEFT_PAREN, scanner.yylex());
			EXPECT_EQ(token::IDENTIFIER, scanner.yylex());
			EXPECT_EQ(token::COMMA, scanner.yylex());
			EXPECT_EQ(token::IDENTIFIER, scanner.yylex());
			EXPECT_EQ(token::RIGHT_PAREN, scanner.yylex());
			EXPECT_EQ(token::SEMICOLON, scanner.yylex());

			EXPECT_EQ(token::PAL_BEGIN, scanner.yylex());
			EXPECT_EQ(token::END, scanner.yylex());
			EXPECT_EQ(token::PERIOD, scanner.yylex());
		}

		input.close();
	}

	TEST(ScannerTest, TestUnclosedComment)
	{
		ifstream input("test/test_cases/testUnclosedComment.pal");

		EXPECT_TRUE(input.is_open()) << "Couldn't open test input file!";

		if (input.is_open())
		{
			ErrorManager errorManager;
			PalScanner scanner(&input, &errorManager);

			EXPECT_EQ(token::PROGRAM, scanner.yylex());
			EXPECT_EQ(token::IDENTIFIER, scanner.yylex());
			EXPECT_EQ(token::LEFT_PAREN, scanner.yylex());
			EXPECT_EQ(token::IDENTIFIER, scanner.yylex());
			EXPECT_EQ(token::COMMA, scanner.yylex());
			EXPECT_EQ(token::IDENTIFIER, scanner.yylex());
			EXPECT_EQ(token::RIGHT_PAREN, scanner.yylex());
			EXPECT_EQ(token::SEMICOLON, scanner.yylex());

			EXPECT_EQ(token::PAL_BEGIN, scanner.yylex());

			// there should be an unclosed comment starting at this point
			// therefore, scanner should just return 0 next as the rest of the file
			// will be commented out.
			EXPECT_EQ(0, scanner.yylex());

			// should only be one error
			vector<const Error*> unclosedErrors;
			const vector<Error*> errors = errorManager.getErrors();

			EXPECT_EQ(errors.size(), 1u); 

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

			EXPECT_EQ(unclosedErrors.size(), 1u);
			if (unclosedErrors.size() > 0)
			{
				const Error* unclosedError = unclosedErrors.front();
				EXPECT_EQ(unclosedError->getLineNumber(), 3u);
			}
		}

		input.close();
	}
}

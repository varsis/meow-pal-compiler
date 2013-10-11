#include <fstream>
#include "gtest/gtest.h"

#include "../src/Scanner.hpp"

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
			PalScanner scanner(&input);

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
			PalScanner scanner(&input);

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
			PalScanner scanner(&input);

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
			PalScanner scanner(&input);

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

			// TODO test error output somehow!! 
			// (eg, check for presence of some error code at some line/column?)

			EXPECT_EQ(0, scanner.yylex());
		}

		input.close();
	}
}

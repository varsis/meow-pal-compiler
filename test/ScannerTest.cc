#include <fstream>
#include "gtest/gtest.h"

#include "../obj/Scanner.hpp"

using namespace std;

namespace Meow
{
	typedef BisonParser::token token;

	TEST(ScannerTest, TestValidInput001)
	{
		ifstream input("test/test_cases/test001.pal");

		EXPECT_TRUE(input.is_open()) << "Couldn't open test input file!";

		if (input.is_open())
		{
			FlexScanner scanner(&input);

			EXPECT_EQ(token::PROGRAM, scanner.yylex());
			EXPECT_EQ(token::IDENTIFIER, scanner.yylex());
			EXPECT_EQ(token::SEMICOLON, scanner.yylex());
			EXPECT_EQ(token::EOLN, scanner.yylex());

			EXPECT_EQ(token::PAL_BEGIN, scanner.yylex());
			EXPECT_EQ(token::EOLN, scanner.yylex());

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
			FlexScanner scanner(&input);

			EXPECT_EQ(token::PROGRAM, scanner.yylex());
			EXPECT_EQ(token::IDENTIFIER, scanner.yylex());
			EXPECT_EQ(token::SEMICOLON, scanner.yylex());
			EXPECT_EQ(token::EOLN, scanner.yylex());

			EXPECT_EQ(token::PAL_BEGIN, scanner.yylex());
			EXPECT_EQ(token::EOLN, scanner.yylex());

				EXPECT_EQ(token::IDENTIFIER, scanner.yylex());
				EXPECT_EQ(token::LEFT_PAREN, scanner.yylex());
				EXPECT_EQ(token::STRING_LITERAL, scanner.yylex());
				EXPECT_EQ(token::RIGHT_PAREN, scanner.yylex());
				EXPECT_EQ(token::SEMICOLON, scanner.yylex());
				EXPECT_EQ(token::EOLN, scanner.yylex());

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
			FlexScanner scanner(&input);

			EXPECT_EQ(token::PROGRAM, scanner.yylex());
			EXPECT_EQ(token::IDENTIFIER, scanner.yylex());
			EXPECT_EQ(token::SEMICOLON, scanner.yylex());
			EXPECT_EQ(token::EOLN, scanner.yylex());

			EXPECT_EQ(token::PAL_BEGIN, scanner.yylex());
			EXPECT_EQ(token::EOLN, scanner.yylex());

				EXPECT_EQ(token::BEGIN_COMMENT, scanner.yylex());
				EXPECT_EQ(token::CLOSE_COMMENT, scanner.yylex());
				EXPECT_EQ(token::EOLN, scanner.yylex());

				EXPECT_EQ(token::EOLN, scanner.yylex());

			EXPECT_EQ(token::END, scanner.yylex());
			EXPECT_EQ(token::PERIOD, scanner.yylex());
		}

		input.close();
	}
}

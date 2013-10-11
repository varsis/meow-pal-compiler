#include "gtest/gtest.h"

#include "../src/pal.tab.h"
#include "../src/Scanner.hpp"
#include "MockScanner.h"

using namespace std;

namespace Meow
{
	typedef PalParser::token token;
	typedef PalParser::token_type token_type;

	class ParserTest : public ::testing::Test
	{
		protected:

			ParserTest() 
				: parser(scanner)
			{
			}

			virtual void SetUp()
			{
				expectedParseResult = 0;
				tokens.clear();
			}

			virtual void TearDown()
			{
				scanner.setTokens(tokens);
				ASSERT_EQ(expectedParseResult, parser.parse()) 
					<< ">> Failed to parse correct input!";
			}

			int expectedParseResult;

			MockScanner scanner;
			vector<token_type> tokens;

			PalParser parser;
	};

	TEST_F(ParserTest, TestMinimalProgram)
	{
		tokens.push_back(token::PROGRAM);
		tokens.push_back(token::IDENTIFIER);
		tokens.push_back(token::LEFT_PAREN);
		tokens.push_back(token::IDENTIFIER);
		tokens.push_back(token::COMMA);
		tokens.push_back(token::IDENTIFIER);
		tokens.push_back(token::RIGHT_PAREN);
		tokens.push_back(token::SEMICOLON);

		tokens.push_back(token::PAL_BEGIN);

		tokens.push_back(token::END);
		tokens.push_back(token::PERIOD);
	}

// Array declaration tests...

	class ArrayDecTest : public ParserTest
	{
		protected:
			virtual void SetUp()
			{
				ParserTest::SetUp();

				tokens.push_back(token::PROGRAM);
				tokens.push_back(token::IDENTIFIER);
				tokens.push_back(token::LEFT_PAREN);
				tokens.push_back(token::IDENTIFIER);
				tokens.push_back(token::COMMA);
				tokens.push_back(token::IDENTIFIER);
				tokens.push_back(token::RIGHT_PAREN);
				tokens.push_back(token::SEMICOLON);
				tokens.push_back(token::TYPE);
				tokens.push_back(token::IDENTIFIER);
				tokens.push_back(token::EQ);
				tokens.push_back(token::ARRAY);
			}

			virtual void TearDown()
			{
				tokens.push_back(token::OF);
				tokens.push_back(token::BOOL);
				tokens.push_back(token::SEMICOLON);
				tokens.push_back(token::PAL_BEGIN);
				tokens.push_back(token::END);
				tokens.push_back(token::PERIOD);

				ParserTest::TearDown();
			}
	};

	TEST_F(ArrayDecTest, TestArrayDeclarations0)
	{
		tokens.push_back(token::LEFT_BRACKET);
		tokens.push_back(token::INT_CONST);
		tokens.push_back(token::UPTO);
		tokens.push_back(token::INT_CONST);
		tokens.push_back(token::RIGHT_BRACKET);
	} // type array[1..10] of bool;

	TEST_F(ArrayDecTest, TestArrayDeclarations1)
	{
		tokens.push_back(token::LEFT_BRACKET);

		tokens.push_back(token::LEFT_PAREN);
		tokens.push_back(token::IDENTIFIER);
		tokens.push_back(token::RIGHT_PAREN);

		tokens.push_back(token::UPTO);

		tokens.push_back(token::LEFT_PAREN);
		tokens.push_back(token::IDENTIFIER);
		tokens.push_back(token::RIGHT_PAREN);

		tokens.push_back(token::RIGHT_BRACKET);
	} // type array[(id) .. (id)] of bool;

	// With the supplied grammar, these are 'legal' but PAL doesn't allow 
	// anonymous enumerations in array types, so the next two SHOULD fail to parse

	TEST_F(ArrayDecTest, TestArrayDeclarations2)
	{
		expectedParseResult = 1;

		tokens.push_back(token::LEFT_BRACKET);
		tokens.push_back(token::LEFT_PAREN);
		tokens.push_back(token::IDENTIFIER);
		tokens.push_back(token::RIGHT_PAREN);
		tokens.push_back(token::RIGHT_BRACKET);
	} // type array[(id)]

	TEST_F(ArrayDecTest, TestArrayDeclarations3)
	{
		expectedParseResult = 1;

		tokens.push_back(token::LEFT_BRACKET);
		tokens.push_back(token::LEFT_PAREN);
		tokens.push_back(token::IDENTIFIER);
		tokens.push_back(token::COMMA);
		tokens.push_back(token::IDENTIFIER);
		tokens.push_back(token::RIGHT_PAREN);
		tokens.push_back(token::RIGHT_BRACKET);
	} // type array[(id, id)] of bool;
}

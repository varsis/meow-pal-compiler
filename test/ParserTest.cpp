#include "gtest/gtest.h"

#include "../src/pal.tab.h"
#include "../src/Scanner.hpp"
#include "MockScanner.h"

using namespace std;

namespace Meow
{
	typedef PalParser::token token;
	typedef PalParser::token_type token_type;

	TEST(ParserTest, TestMinimalProgram)
	{
		MockScanner scanner;

		vector<token_type> tokens;

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

		scanner.setTokens(tokens);

		PalParser parser(scanner);

		ASSERT_EQ(0, parser.parse()) << ">> Failed to parse correct input!";
	}

// Array declaration tests...
// This probably looks rather voodo, there's probably a nicer way to do this using test 
// fixture classes but then we'll need to make a whole lot of files for test classes

#define ARRAY_DEC_TEST(ARRAY_DEC_TEST_NAME)\
	TEST(ParserTest, ARRAY_DEC_TEST_NAME)\
	{\
		MockScanner scanner;\
		vector<token_type> tokens;\
		tokens.push_back(token::PROGRAM);\
		tokens.push_back(token::IDENTIFIER);\
		tokens.push_back(token::LEFT_PAREN);\
		tokens.push_back(token::IDENTIFIER);\
		tokens.push_back(token::COMMA);\
		tokens.push_back(token::IDENTIFIER);\
		tokens.push_back(token::RIGHT_PAREN);\
		tokens.push_back(token::SEMICOLON);\
		tokens.push_back(token::TYPE);\
		tokens.push_back(token::IDENTIFIER);\
		tokens.push_back(token::EQ);\
		tokens.push_back(token::ARRAY);


#define ARRAY_DEC_TEST_END(ARRAY_DEC_TEST_STRING)\
		tokens.push_back(token::OF);\
		tokens.push_back(token::BOOL);\
		tokens.push_back(token::SEMICOLON);\
		tokens.push_back(token::PAL_BEGIN);\
		tokens.push_back(token::END);\
		tokens.push_back(token::PERIOD);\
		scanner.setTokens(tokens);\
		PalParser parser(scanner);\
		ASSERT_EQ(0, parser.parse()) << ARRAY_DEC_TEST_STRING; \
	}

	ARRAY_DEC_TEST(TestArrayDeclarations0)
		tokens.push_back(token::LEFT_BRACKET);
		tokens.push_back(token::INT_CONST);
		tokens.push_back(token::UPTO);
		tokens.push_back(token::INT_CONST);
		tokens.push_back(token::RIGHT_BRACKET);
	ARRAY_DEC_TEST_END("type array[1..10] of bool;")

	ARRAY_DEC_TEST(TestArrayDeclarations1)
		tokens.push_back(token::LEFT_BRACKET);
		tokens.push_back(token::LEFT_PAREN);
		tokens.push_back(token::IDENTIFIER);
		tokens.push_back(token::RIGHT_PAREN);
		tokens.push_back(token::RIGHT_BRACKET);
	ARRAY_DEC_TEST_END("type array[(id)] of bool;")

	ARRAY_DEC_TEST(TestArrayDeclarations2)
		tokens.push_back(token::LEFT_BRACKET);
		tokens.push_back(token::LEFT_PAREN);
		tokens.push_back(token::IDENTIFIER);
		tokens.push_back(token::COMMA);
		tokens.push_back(token::IDENTIFIER);
		tokens.push_back(token::RIGHT_PAREN);
		tokens.push_back(token::RIGHT_BRACKET);
	ARRAY_DEC_TEST_END("type array[(id, id)] of bool;")

	// Next one is tricky...
	// Reduce/Reduce conflict in given grammar makes assumption that (id) is 
	// a 'scalar_list', then it explodes when it sees the '..'

	ARRAY_DEC_TEST(TestArrayDeclarations3)
		tokens.push_back(token::LEFT_BRACKET);

		tokens.push_back(token::LEFT_PAREN);
		tokens.push_back(token::IDENTIFIER);
		tokens.push_back(token::RIGHT_PAREN);

		tokens.push_back(token::UPTO);

		tokens.push_back(token::LEFT_PAREN);
		tokens.push_back(token::IDENTIFIER);
		tokens.push_back(token::RIGHT_PAREN);

		tokens.push_back(token::RIGHT_BRACKET);
	ARRAY_DEC_TEST_END("type array[(false) .. (true)] of bool;")
}

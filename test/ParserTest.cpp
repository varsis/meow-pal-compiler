#include "gtest/gtest.h"

#include "../src/pal.tab.h"
#include "../src/Scanner.hpp"
#include "MockScanner.h"

using namespace std;

namespace Meow
{
	typedef PalParser::token token;
	typedef PalParser::token_type token_type;

	TEST(ParserTest, Test001)
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
		tokens.push_back(token::EOLN);

		tokens.push_back(token::PAL_BEGIN);
		tokens.push_back(token::EOLN);

		tokens.push_back(token::END);
		tokens.push_back(token::PERIOD);

		scanner.setTokens(tokens);

		PalParser parser(scanner);

		ASSERT_EQ(0, parser.parse()) << ">> Failed to parse correct input!";
	}
}

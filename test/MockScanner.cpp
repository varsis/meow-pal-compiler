#include <vector>
#include "MockScanner.h"
#include "../src/Parser.hpp"
#include "../src/pal.tab.hpp"

using namespace std;

namespace Meow
{
	//--------------------------------------------------------------------------------
	// MockScanner::setTokens
	//--------------------------------------------------------------------------------
	// Sets the stream of tokens that this mock scanner will spit out with yylex()
	//--------------------------------------------------------------------------------
	void MockScanner::setTokens(vector<PalParser::token_type> tokenStream)
	{
		m_tokens = tokenStream;
		m_tokenIterator = m_tokens.begin();
	}

	//--------------------------------------------------------------------------------
	// MockScanner::yylex(yylval)
	//--------------------------------------------------------------------------------
	// So parser doesn't explode, provide dummy strings in yylval when necessary
	//--------------------------------------------------------------------------------
	int MockScanner::yylex(PalParser::semantic_type * lval)
	{
		int token = yylex();

		switch (token)
		{
			case token::IDENTIFIER:
				lval->identifier = new std::string("dummyid");
				break;

			case token::STRING_LITERAL:
				lval->stringLiteral = new std::string("dummystring");
				break;
		}

		return token;
	}

	//--------------------------------------------------------------------------------
	// MockScanner::yylex
	//--------------------------------------------------------------------------------
	// Returns the next token in the vector of predefined tokens
	//--------------------------------------------------------------------------------
	int MockScanner::yylex()
	{
		if (m_tokenIterator != m_tokens.end())
		{
			PalParser::token_type token = *m_tokenIterator;
			++m_tokenIterator; // advance to next token;
			return token;
		}

		return 0; // outta tokens!
	}
}

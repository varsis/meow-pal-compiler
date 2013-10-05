#include <vector>
#include "MockScanner.h"
#include "../src/pal.tab.h"

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

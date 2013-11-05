#include <vector>
#include "../src/Scanner.hpp"

#ifndef MOCKSCANNER_H
#define MOCKSCANNER_H

namespace Meow
{
	typedef PalParser::token token;
	typedef PalParser::token_type token_type;

	class MockScanner : public PalScanner
	{
		public:

		   	MockScanner() 
				: PalScanner(NULL, NULL)
			{
			}

			void setTokens(std::vector<PalParser::token_type> tokenStream);

			virtual int yylex(PalParser::semantic_type * lval);
			virtual int yylex();

		private:

			std::vector<PalParser::token_type>::iterator m_tokenIterator;
			std::vector<PalParser::token_type> m_tokens;
	};
}
#endif

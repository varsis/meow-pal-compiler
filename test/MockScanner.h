#include <vector>
#include "../src/Scanner.hpp"

#ifndef MOCKSCANNER_H
#define MOCKSCANNER_H

namespace Meow
{
	class MockScanner : public PalScanner
	{
		public:

		   	MockScanner() {}

			void setTokens(std::vector<PalParser::token_type> tokenStream);

			virtual int yylex();

		private:

			std::vector<PalParser::token_type>::iterator m_tokenIterator;
			std::vector<PalParser::token_type> m_tokens;
	};
}
#endif

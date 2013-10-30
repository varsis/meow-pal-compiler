#ifndef SCANNER_H
#define SCANNER_H

// Only include FlexLexer.h if it hasn't been already included
#if ! defined(yyFlexLexerOnce)
#include <FlexLexer.h>
#endif

#include <assert.h>

#include "ErrorCodes.hpp"
#include "Error.hpp"
#include "ErrorManager.hpp"

// Override the interface for yylex since we namespaced it
#undef YY_DECL
#define YY_DECL int Meow::PalScanner::yylex()

// Include Bison for types / tokens
#include "pal.tab.hpp"

namespace Meow
{
	class PalScanner : public yyFlexLexer
	{
		public:

			PalScanner(FLEX_STD istream* arg_yyin, ErrorManager * manager)
				: yyFlexLexer(arg_yyin, 0)
			{
				this->m_manager = manager;
			}

			// save the pointer to yylval so we can change it, and invoke scanner
			virtual int yylex(PalParser::semantic_type * lval)
			{
				yylval = lval;
				int token = yylex();
				return token;
			}

		private:
			virtual int yylex();

			ErrorManager * getManager() 
			{
				return m_manager;
			};

			ErrorManager * m_manager;
			// point to yylval (provided by Bison in overloaded yylex)
			PalParser::semantic_type * yylval;
	};
}

#endif

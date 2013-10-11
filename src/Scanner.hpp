#pragma once

// Only include FlexLexer.h if it hasn't been already included
#if ! defined(yyFlexLexerOnce)
#include <FlexLexer.h>
#endif

#include "errorcodes.hpp"
#include "error.hpp"
#include "errormanager.hpp"

// Override the interface for yylex since we namespaced it
#undef YY_DECL
#define YY_DECL int Meow::PalScanner::yylex()

// Include Bison for types / tokens
#include "pal.tab.h"

namespace Meow
{
	class PalScanner : public yyFlexLexer
	{
		public:

			PalScanner( FLEX_STD istream* arg_yyin = 0, FLEX_STD ostream* arg_yyout = 0 , ErrorManager * manager = 0)
				: yyFlexLexer(arg_yyin, arg_yyout)
			{
                this->m_manager = manager;
			}

			virtual int yylex();

			// save the pointer to yylval so we can change it, and invoke scanner
			virtual int yylex(PalParser::semantic_type * lval)
			{
				yylval = lval;
				return yylex();
			}
        
        
        
		
		private:
            ErrorManager * m_manager;
			// point to yylval (provided by Bison in overloaded yylex)
			PalParser::semantic_type * yylval;
	};
}


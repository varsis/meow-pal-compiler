%{
	#include <iostream>
	#include <string>
	#include "Scanner.hpp"
	#include "SymbolTable.hpp"
	typedef Meow::PalParser::token token;

	static bool s_stringInvalid;
	static bool s_stringMultiline;
	static int s_commentStartLine;
	static int s_scannerReturnPosition;
	static int s_scannerReturnLine;

	extern int g_whileCounter;
	extern int g_beginCounter;
%}

%option nodefault yyclass="PalScanner" noyywrap c++
%option yylineno

%x IN_COMMENT
%x IN_STRING_LITERAL

DIGIT 		[0-9]
EXPONENT	E[+-]?{DIGIT}+

%%

<IN_COMMENT>
{
	"}"	{ BEGIN(INITIAL); }
	\n	{ /* Count line endings */ }
	<<EOF>> {
			getManager()->addError(new Error(UnclosedComment, "Unclosed comment.", s_commentStartLine));
			return 0;
		}
	.	{ /* ignore eveything else */ }
}

<IN_STRING_LITERAL>
{
	\\[^nt'\\] 	{
			if (!s_stringInvalid)
			{
				getManager()->addError(new Error(InvalidString, "String contains invalid escapes.", s_commentStartLine));
				s_stringInvalid = true;
			}
		}
	\\'	{ /* empty */ }
	\\n	{ /* empty */ }
	\\t	{ /* empty */ }
	\\\\	{ /* empty */ }
	'	{
			if (s_stringMultiline)
			{
				// resume scanning from saved position
				yyin->seekg(s_scannerReturnPosition);
				yylineno = s_scannerReturnLine;
			}

			BEGIN(INITIAL);
			yylval->stringLiteral = new std::string(yytext);
			return token::STRING_LITERAL;
		}
	\n	{ /* Count line endings */
			if (!s_stringMultiline)
			{
				getManager()->addError(new Error(MultiLineString, "Unclosed / Multiline string; invalid", s_commentStartLine));
				s_stringMultiline = true;

				// save position to resume scanning from
				s_scannerReturnPosition = yyin->tellg();
				s_scannerReturnLine = yylineno;
			}
		}
	<<EOF>> {
			if (!s_stringMultiline)
			{
				getManager()->addError(new Error(UnclosedString, "Unclosed string.", s_commentStartLine));
			}

			if (s_stringMultiline)
			{
				// resume scanning from saved position
				yyin->seekg(s_scannerReturnPosition);
				yylineno = s_scannerReturnLine;
				BEGIN(INITIAL);
				yylval->stringLiteral = new std::string(yytext);
				return token::STRING_LITERAL;
			}

			return 0;
		}
		
	.	{ /* ignore eveything else */ }
}

[ \t] 	{ ; /* Ignore whitespace */ }
\n 	{ ; /* Count line endings */ }
"//".*[^\n] { ; /* Ignore single line comments */ }

"{" 	{ 
		s_commentStartLine = yylineno;
		BEGIN(IN_COMMENT); 
	}
	
'	{
		s_stringInvalid = false;
		s_stringMultiline = false;
		s_commentStartLine = yylineno;
		BEGIN(IN_STRING_LITERAL);
	}
	
\" 	{
		s_stringInvalid = false;
		s_stringMultiline = false;
		s_commentStartLine = yylineno;
		getManager()->addError(new Error(UnmatchedComment, "\" ' \" expected for string literal.", yylineno));
		BEGIN(IN_STRING_LITERAL);
	}

"}" { getManager()->addError(new Error(UnmatchedComment, "Unexpected \"}\"; unmatched comment.", yylineno)); }

"\[" { return token::LEFT_BRACKET; }
"\]" { return token::RIGHT_BRACKET; }
"\(" { return token::LEFT_PAREN; }
"\)" { return token::RIGHT_PAREN; }

"<=" { return token::LE; }
">=" { return token::GE; }
"<>" { return token::NE; }
"=" { return token::EQ; }
"<" { return token::LT; }
">" { return token::GT; }

":=" { return token::ASSIGN; }
"." {return token::PERIOD; }
".." {return token::UPTO; }
".."[\.]* {
	getManager()->addError(new Error(InvalidUpTo, "Too many dots; should be \"..\".", yylineno));
	return token::UPTO;
	}

"+" { return token::PLUS; }
"-" { return token::MINUS; }
"*" { return token::MULTIPLY; }
"/" { return token::REAL_DIVIDE; }
"div" { return token::INT_DIVIDE; }
"mod" { return token::MOD; }

"and" { return token::AND; }
"array" { return token::ARRAY; }
"begin" { g_beginCounter++; return token::PAL_BEGIN; }
"const" { return token::CONST; }
"continue" { 
	if (!g_whileCounter) 
	{
		getManager()->addError(new Error(InvalidExitContinue,
						"Invalid continue; must be in while loop.",
						yylineno));
	}
	
	return token::CONTINUE; 
	}
"do" { g_whileCounter++; return token::DO; }
"else" { return token::ELSE; }
"end" {
	if(g_beginCounter)
	{
		g_beginCounter--;
	}

	if(!g_beginCounter)
	{
		m_symbolTable->decLevel();
	}

	return token::END; 
	}
"exit" { 
	if (!g_whileCounter) 
	{
		getManager()->addError(new Error(InvalidExitContinue,
						"Invalid exit; must be in while loop.",
						yylineno));
	}
	return token::EXIT; 
	}
"function" { return token::FUNCTION; }
"if" { return token::IF; }
"not" { return token::NOT; }
"of" { return token::OF; }
"or" { return token::OR; }
"procedure" { return token::PROCEDURE; }
"program" { return token::PROGRAM; }
"record" { return token::RECORD; }
"then" { return token::THEN; }
"type" { return token::TYPE; }
"var" { return token::VAR; }
"while" { return token::WHILE; }

{DIGIT}+((\.{DIGIT}+{EXPONENT})|(\.{DIGIT}+)|{EXPONENT}) { 
	yylval->realConst = atof(yytext);
	return token::REAL_CONST; 
							 }
{DIGIT}+ {
	yylval->intConst = atoi(yytext);
	return token::INT_CONST;
	 }

([a-zA-Z]+[0-9a-zA-Z]*) { 
				yylval->identifier = new std::string(yytext);
				return token::IDENTIFIER;
			}
([0-9]+[a-zA-Z0-9]*) 	{ 
				getManager()->addError(new Error(InvalidIdentifier, "Identifiers may not begin with numbers.", yylineno));
				yylval->identifier = new std::string(yytext);
				return token::IDENTIFIER; 
			}

"," { return token::COMMA; }
";" { return token::SEMICOLON; }
":" { return token::COLON; }

. { getManager()->addError(new Error(UnrecognizedSymbol, "Invalid symbol encountered.", yylineno)); }

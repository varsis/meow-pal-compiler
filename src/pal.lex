%{
	#include <iostream>
	#include "Scanner.hpp"
	typedef Meow::PalParser::token token;

	static unsigned int s_commentStartLine;
%}

%option nodefault yyclass="PalScanner" noyywrap c++
%option yylineno

%x IN_COMMENT

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

[ \t] { ; /* Ignore whitespace */ }
\n 	{ ; /* Count line endings */ }
"//".*[^\n] { ; /* Ignore single line comments */ }

"{" { 
		s_commentStartLine = yylineno;
		BEGIN(IN_COMMENT); 
	}

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

"+" { return token::ADD; }
"-" { return token::SUBTRACT; }
"*" { return token::MULTIPLY; }
"/" { return token::REAL_DIVIDE; }
"div" { return token::INT_DIVIDE; }
"mod" { return token::MOD; }

"and" { return token::AND; }
"array" { return token::ARRAY; }
"begin" { return token::PAL_BEGIN; }
"const" { return token::CONST; }
"continue" { return token::CONTINUE; }
"do" { return token::DO; }
"else" { return token::ELSE; }
"end" { return token::END; }
"exit" { return token::EXIT; }
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

'(\\.|[^'\n])*' {yylval->stringLiteral = new std::string(yytext); return token::STRING_LITERAL;} /* TODO check for valid escapes, etc */
'(\\.|[^'\n])* {yylval->stringLiteral = new std::string(yytext); getManager()->addError(new Error(UnclosedString, "Unclosed string literal.", yylineno));}

[+-]?(0|[1-9])+((\.[0-9]+)|([E][-+]?[0-9]+))+ { return token::REAL_CONST; }
[+-]?(0|[1-9])+ {  return token::INT_CONST; }
([a-zA-Z]+[0-9a-zA-Z]*) { return token::IDENTIFIER; }
([0-9_]*[a-zA-Z_0-9]*) { yylval->identifier = new std::string(yytext); getManager()->addError(new Error(InvalidIdentifier, "Identifiers may not contain underscores or begin with numbers.", yylineno)); }

"," { return token::COMMA; }
";" { return token::SEMICOLON; }
":" { return token::COLON; }

. { getManager()->addError(new Error(UnrecognizedSymbol, "Invalid symbol encountered.", yylineno)); }


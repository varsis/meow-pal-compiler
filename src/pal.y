%require "2.4.1"
%skeleton "lalr1.cc"
%defines
%define namespace "Meow"
%define parser_class_name "BisonParser"
%parse-param { Meow::FlexScanner &scanner }
%lex-param   { Meow::FlexScanner &scanner }

%code requires {
	// Forward-declare the Scanner class; the Parser needs to be assigned a 
	// Scanner, but the Scanner can't be declared without the Parser
	namespace Meow {
		class FlexScanner;
	}
}

%code {
	// Prototype for the yylex function
	static int yylex(Meow::BisonParser::semantic_type * yylval, Meow::FlexScanner &scanner);
	void print_error(const std::string msg);
	void print_value(bool value);
}

%code {
	#include <utility>
}

%union {
	std::string* identifier;
}

%token <identifier> IDENTIFIER

%token ASSIGN
%token LEFT_BRACKET RIGHT_BRACKET
%token LEFT_PAREN RIGHT_PAREN
%token SEMICOLON EOLN
%token LE GE NE EQ LT GT
%token ADD SUBTRACT MULTIPLY REAL_DIVIDE INT_DIVIDE MOD DIV
%token AND ARRAY BOOL CHAR CONST CONTINUE DO ELSE END EXIT
%token FUNCTION IF NOT OF OR PROCEDURE PROGRAM RECORD THEN
%token TYPE VAR WHILE PAL_BEGIN INT
%token BEGIN_COMMENT CLOSE_COMMENT STRING_LITERAL
%token INT_CONST REAL_CONST

%%

Program
	: /* empty */
	| Program EOLN
	| Program Statement EOLN
	;

Statement
	: BEGIN_COMMENT CLOSE_COMMENT EOLN { std::cout << "Multi-line comment.\n"; }
	| error EOLN { ; }
%%

void print_error(const std::string msg) {
	std::cerr << msg << std::endl;
}

// We have to implement the error function
void Meow::BisonParser::error(const Meow::BisonParser::location_type &loc, const std::string &msg) { }

// Now that we have the Parser declared, we can declare the Scanner and implement
// the yylex function
#include "Scanner.hpp"
static int yylex(Meow::BisonParser::semantic_type * yylval, Meow::FlexScanner &scanner) {
	return scanner.yylex(yylval);
}

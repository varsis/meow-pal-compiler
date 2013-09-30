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
%token TYPE VAR WHILE PAL_BEGIN
%token INT REAL
%token BEGIN_COMMENT CLOSE_COMMENT STRING_LITERAL
%token INT_CONST REAL_CONST

%%

program                 : program_head decls compound_stat '.'
                        ;

program_head            : PROGRAM IDENTIFIER '(' IDENTIFIER ',' IDENTIFIER ')' ';'
                        ;

decls                   : const_decl_part
                          type_decl_part        
                          var_decl_part
                          proc_decl_part
                        ;

const_decl_part         : CONST const_decl_list ';'
                        |
                        ;

const_decl_list         : const_decl
                        | const_decl_list ';' const_decl
                        ;

const_decl              : IDENTIFIER EQ expr
                        ;

type_decl_part          : TYPE type_decl_list ';'
                        |
                        ;

type_decl_list          : type_decl
                        | type_decl_list ';' type_decl
                        ;

type_decl               : IDENTIFIER EQ type
                        ;

type                    : simple_type
                        | structured_type
                        ;

simple_type             : scalar_type
                        : REAL
                        | IDENTIFIER
                        ;

scalar_type             : '(' scalar_list ')'
                        | INT
                        | BOOL
                        | CHAR
                        ;

scalar_list             : IDENTIFIER
                        | scalar_list ',' IDENTIFIER
                        ;

structured_type         : ARRAY '[' array_type ']' OF type
                        | RECORD field_list END
                        ;

array_type              : simple_type
                        | expr ".." expr
                        ;

field_list              : field
                        | field_list ';' field
                        ;

field                   : IDENTIFIER ':' type
                        ;

var_decl_part           : VAR var_decl_list ';'
                        |
                        ;

var_decl_list           : var_decl
                        | var_decl_list ';' var_decl
                        ;

var_decl                : IDENTIFIER ':' type
                        | IDENTIFIER ',' var_decl
                        ;

proc_decl_part          : proc_decl_list
                        |
                        ;

proc_decl_list          : proc_decl
                        | proc_decl_list proc_decl
                        ;

proc_decl               : proc_heading decls compound_stat ';'
                        ;

proc_heading            : PROCEDURE IDENTIFIER f_parm_decl ';'
                        | FUNCTION IDENTIFIER f_parm_decl ':' IDENTIFIER ';'
                        ;

f_parm_decl             : '(' f_parm_list ')'
                        | '(' ')'
                        ;

f_parm_list             : f_parm
                        | f_parm_list ';' f_parm
                        ;

f_parm                  : IDENTIFIER ':' IDENTIFIER
                        | VAR IDENTIFIER ':' IDENTIFIER
                        ;

compound_stat           : PAL_BEGIN stat_list END
                        ;       

stat_list               : stat
                        | stat_list ';' stat
                        ;

stat                    : simple_stat
                        | struct_stat
                        |
                        ;

simple_stat             : var ASSIGN expr
                        | proc_invok
                        | compound_stat
                        ;

proc_invok              : plist_finvok ')'
                        | IDENTIFIER '(' ')'
                        ;

var                     : IDENTIFIER
                        | var '.' IDENTIFIER
                        | subscripted_var ']'
                        ;

subscripted_var         : var '[' expr
                        | subscripted_var ',' expr
                        ;

expr                    : simple_expr
                        | expr EQ simple_expr
                        | expr NE simple_expr
                        | expr LE simple_expr
                        | expr LT simple_expr
                        | expr GE simple_expr
                        | expr GT simple_expr
                        ;

expr_list               : expr_list ',' expr
                        | expr
                        ;

simple_expr             : term
                        | ADD term
                        | SUBTRACT term
                        | simple_expr ADD term
                        | simple_expr SUBTRACT term
                        | simple_expr OR  term
                        ;

term                    : factor
                        | term MULTIPLY factor
                        | term REAL_DIVIDE factor
                        | term INT_DIVIDE factor
                        | term MOD factor
                        | term AND factor
                        ;

factor                  : var
                        | unsigned_const
                        | '(' expr ')'
                        | func_invok
                        | NOT factor
                        ;

unsigned_const          : unsigned_num
                        | IDENTIFIER
                        | STRING_LITERAL
                        ;

unsigned_num            : INT_CONST
                        | REAL_CONST
                        ;

func_invok              : plist_finvok ')'
                        | IDENTIFIER '(' ')'
                        ;

plist_finvok            : IDENTIFIER '(' parm
                        | plist_finvok ',' parm
                        ;

parm                    : expr

struct_stat             : IF expr THEN matched_stat ELSE stat
                        | IF expr THEN stat
                        | WHILE expr DO stat
                        | CONTINUE
                        | EXIT
                        ;

matched_stat            : simple_stat
                        | IF expr THEN matched_stat ELSE matched_stat
                        | WHILE expr DO matched_stat
                        | CONTINUE
                        | EXIT
                        ;
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

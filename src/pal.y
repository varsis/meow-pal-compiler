%require "2.4.1"
%skeleton "lalr1.cc"
%defines
%define namespace "Meow"
%define parser_class_name "PalParser"
%parse-param { Meow::PalScanner &scanner }
%lex-param   { Meow::PalScanner &scanner }

%code requires {
	// Forward-declare the Scanner class; the Parser needs to be assigned a 
	// Scanner, but the Scanner can't be declared without the Parser
	namespace Meow {
		class PalScanner;
	}
}

%code {
	// Prototype for the yylex function
	static int yylex(Meow::PalParser::semantic_type * yylval, Meow::PalScanner &scanner);
	void print_error(const std::string msg);
	void print_value(bool value);
}

%union {
	std::string* identifier;
}

%token <identifier> IDENTIFIER

%token ASSIGN
%token LEFT_BRACKET RIGHT_BRACKET
%token LEFT_PAREN RIGHT_PAREN
%token COLON SEMICOLON
%token COMMA PERIOD
%token UPTO
%token LE GE NE EQ LT GT
%token ADD SUBTRACT MULTIPLY REAL_DIVIDE INT_DIVIDE MOD DIV
%token AND ARRAY BOOL CHAR CONST CONTINUE DO ELSE END EXIT
%token FUNCTION IF NOT OF OR PROCEDURE PROGRAM RECORD THEN
%token TYPE VAR WHILE PAL_BEGIN
%token INT REAL
%token BEGIN_COMMENT CLOSE_COMMENT STRING_LITERAL
%token INT_CONST REAL_CONST

%%

program                 : program_head decls compound_stat PERIOD
                        ;

program_head            : PROGRAM IDENTIFIER 
							LEFT_PAREN IDENTIFIER COMMA IDENTIFIER RIGHT_PAREN 
							SEMICOLON
                        ;

/********************************************************************************
 * Rules for declarations...
 ********************************************************************************/

decls                   : const_decl_part
                          type_decl_part        
                          var_decl_part
                          proc_decl_part
                        ;

/********************************************************************************
 * Rules for constant declarations...
 ********************************************************************************/
const_decl_part         : CONST const_decl_list SEMICOLON
                        |
                        ;

const_decl_list         : const_decl
                        | const_decl_list SEMICOLON const_decl
                        ;

const_decl              : IDENTIFIER EQ expr
						;

/********************************************************************************
 * Rules for type declarations...
 ********************************************************************************/
type_decl_part          : TYPE type_decl_list SEMICOLON
                        |
                        ;

type_decl_list          : type_decl
                        | type_decl_list SEMICOLON type_decl
                        ;

type_decl               : IDENTIFIER EQ type
                        ;

type                    : simple_type
                        | structured_type
                        ;

simple_type             : scalar_type
                        | REAL
                        | IDENTIFIER
                        ;

scalar_type             : LEFT_PAREN scalar_list RIGHT_PAREN
                        | INT
                        | BOOL
                        | CHAR
                        ;

scalar_list             : IDENTIFIER
                        | scalar_list COMMA IDENTIFIER
                        ;

structured_type         : ARRAY LEFT_BRACKET index_type RIGHT_BRACKET OF type
                        | RECORD field_list END
                        ;

index_type              : simple_type
                        | expr UPTO expr
                        ;

field_list              : field
                        | field_list SEMICOLON field
                        ;

field                   : IDENTIFIER COLON type
                        ;

/********************************************************************************
 * Rules for variable declarations...
 ********************************************************************************/
var_decl_part           : VAR var_decl_list SEMICOLON 
                        |
                        ;

var_decl_list           : var_decl
                        | var_decl_list SEMICOLON var_decl
                        ;

var_decl                : IDENTIFIER COLON type
                        | IDENTIFIER COMMA var_decl
                        ;

/********************************************************************************
 * Rules for procedure + function declarations...
 ********************************************************************************/
proc_decl_part          : proc_decl_list
                        |
                        ;

proc_decl_list          : proc_decl
                        | proc_decl_list proc_decl
                        ;

proc_decl               : proc_heading decls compound_stat SEMICOLON
                        ;

proc_heading            : PROCEDURE IDENTIFIER f_parm_decl SEMICOLON 
                        | FUNCTION IDENTIFIER f_parm_decl COLON IDENTIFIER SEMICOLON
                        ;

f_parm_decl             : LEFT_PAREN f_parm_list RIGHT_PAREN
                        | LEFT_PAREN RIGHT_PAREN
                        ;

f_parm_list             : f_parm
                        | f_parm_list SEMICOLON f_parm
                        ;

f_parm                  : IDENTIFIER COLON IDENTIFIER
                        | VAR IDENTIFIER COLON IDENTIFIER
                        ;

/********************************************************************************
 * Rules for statements
 ********************************************************************************/

compound_stat           : PAL_BEGIN stat_list END
						;

stat_list               : stat
                        | stat_list SEMICOLON stat
                        ;

stat                    : simple_stat
                        | struct_stat
                        |
                        ;

simple_stat             : var ASSIGN expr
                        | proc_invok
                        | compound_stat
                        ;

var                     : IDENTIFIER
                        | var PERIOD IDENTIFIER
                        | subscripted_var RIGHT_BRACKET
                        ;

subscripted_var         : var LEFT_BRACKET expr
                        | subscripted_var COMMA expr
                        ;

proc_invok              : plist_finvok RIGHT_PAREN
                        | IDENTIFIER LEFT_PAREN RIGHT_PAREN
                        ;

plist_finvok            : IDENTIFIER LEFT_PAREN parm
                        | plist_finvok COMMA parm
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

/********************************************************************************
 * Rules for expressions
 ********************************************************************************/

expr                    : simple_expr
                        | expr EQ simple_expr
                        | expr NE simple_expr
                        | expr LE simple_expr
                        | expr LT simple_expr
                        | expr GE simple_expr
                        | expr GT simple_expr
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
                        | LEFT_PAREN expr RIGHT_PAREN
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


func_invok              : plist_finvok RIGHT_PAREN
                        | IDENTIFIER LEFT_PAREN RIGHT_PAREN
                        ;

%%

void print_error(const std::string msg) {
	std::cerr << msg << std::endl;
}

// We have to implement the error function
void Meow::PalParser::error(const Meow::PalParser::location_type &loc, const std::string &msg) { }

// Now that we have the Parser declared, we can declare the Scanner and implement
// the yylex function
#include "Scanner.hpp"
static int yylex(Meow::PalParser::semantic_type * yylval, Meow::PalScanner &scanner) {
	return scanner.yylex(yylval);
}

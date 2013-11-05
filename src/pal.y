%require "2.4.1"
%skeleton "lalr1.cc"
%defines
%define namespace "Meow"
%define parser_class_name "PalParser"
%parse-param { Meow::PalScanner &scanner }
%parse-param { Meow::ErrorManager &errorManager }
%parse-param { Meow::SymbolTable &table }
%lex-param   { Meow::PalScanner &scanner }

%debug
%error-verbose

%code requires {
	// Forward-declare the Scanner class; the Parser needs to be assigned a 
	// Scanner, but the Scanner can't be declared without the Parser
	namespace Meow
	{
		class PalScanner;
		class ErrorManager;
		class SymbolTable;
	}
}

%code {
 	#include "Scanner.hpp"

	#include "ErrorManager.hpp"
	#include "Error.hpp"
 	#include "ErrorCodes.hpp"
 	#include "SymbolTable.hpp"

	#define YYDEBUG 1

	// Prototype for the yylex function
	static int yylex(Meow::PalParser::semantic_type * yylval, Meow::PalScanner &scanner);
	void print_error(const std::string msg);
	void print_value(bool value);
}

%union {
	std::string* identifier;
        std::string* stringLiteral;
}

%token <identifier> IDENTIFIER
%token <stringLiteral> STRING_LITERAL

%token ASSIGN
%token LEFT_BRACKET RIGHT_BRACKET
%token LEFT_PAREN RIGHT_PAREN
%token COLON SEMICOLON
%token COMMA PERIOD
%token UPTO
%token LE GE NE EQ LT GT
%token PLUS MINUS MULTIPLY REAL_DIVIDE INT_DIVIDE MOD DIV
%token AND ARRAY CONST CONTINUE DO ELSE END EXIT
%token FUNCTION IF NOT OF OR PROCEDURE PROGRAM RECORD THEN
%token TYPE VAR WHILE PAL_BEGIN
%token INT_CONST REAL_CONST
%%

program                 : program_head decls compound_stat PERIOD
                        | program_head decls compound_stat 
                        { errorManager.addError(
                              new Error(MissingProgramPeriod,
                                        "Expected \".\" after END", 
                                        scanner.lineno()-1)); 
                        }
                        ;

program_head            : PROGRAM IDENTIFIER 
				LEFT_PAREN IDENTIFIER COMMA IDENTIFIER RIGHT_PAREN
				SEMICOLON
                        | PROGRAM IDENTIFIER 
				LEFT_PAREN IDENTIFIER COMMA IDENTIFIER
				SEMICOLON      
                        { errorManager.addError(
				 new Error(MissingProgramParentheses,
                                   	"Missing \")\" after program argument list.", 
                                   	scanner.lineno())); 
                        }
                        | PROGRAM IDENTIFIER 
				LEFT_PAREN IDENTIFIER COMMA IDENTIFIER RIGHT_PAREN
                        { errorManager.addError(
				 new Error(InvalidProgramHeader,
                                   	"Missing \";\" after program header.", 
                                   	scanner.lineno())); 
                        }
			| PROGRAM IDENTIFIER
				LEFT_PAREN error RIGHT_PAREN SEMICOLON
                        { errorManager.addError(
				 new Error(InvalidProgramHeader,
					"Error in program arguments.",
					 scanner.lineno()));
                        }
                        | /* empty */
                        {
                            errorManager.addError(
			     new Error(InvalidProgramHeader,
					"Missing program header.",
					scanner.lineno()));
                        }
                        | error { ; }
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

const_decl              : IDENTIFIER EQ type_expr
                        {
				Symbol* sym = table.getSymbolCurLevel(*$1);

				if (sym)
				{
					errorManager.addError(new Error(IdentifierInUse,
									"Identifier was already declared at current lexical level.",
									scanner.lineno()));
				}

				sym = new Symbol(*$1, ConstantSymbol);

                                delete $1;

				table.addSymbol(sym);
                        }
			| IDENTIFIER EQ STRING_LITERAL
                        {
				Symbol* sym = table.getSymbolCurLevel(*$1);

				if (sym)
				{
					errorManager.addError(new Error(IdentifierInUse,
									"Identifier was already declared at current lexical level.",
									scanner.lineno()));
				}

				sym = new Symbol(*$1, ConstantSymbol);

                                delete $1;

				table.addSymbol(sym);
                        }
			| IDENTIFIER EQ REAL_CONST
                        {
				Symbol* sym = table.getSymbolCurLevel(*$1);

				if (sym)
				{
					errorManager.addError(new Error(IdentifierInUse,
									"Identifier was already declared at current lexical level.",
									scanner.lineno()));
				}

				sym = new Symbol(*$1, ConstantSymbol);

                                delete $1;

				table.addSymbol(sym);
                        }
                        | IDENTIFIER ASSIGN type_expr
                        {       
                                errorManager.addError(
                                    new Error(InvalidConstDecl,
                                              "Use \"=\" to assign constants.",
                                              scanner.lineno()));

				Symbol* sym = table.getSymbolCurLevel(*$1);

				if (sym)
				{
					errorManager.addError(new Error(IdentifierInUse,
									"Identifier was already declared at current lexical level.",
									scanner.lineno()));
				}

				sym = new Symbol(*$1, ConstantSymbol);

                                delete $1;

				table.addSymbol(sym);
                        }
                        | IDENTIFIER error
                        {
                                errorManager.addError(
                                    new Error(InvalidConstDecl,
                                          "Invalid constant declaration.",
                                          scanner.lineno()));
                        }
                        | error { ; }
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
			{
				Symbol* sym = table.getSymbolCurLevel(*$1);

				if (sym)
				{
					errorManager.addError(new Error(IdentifierInUse,
									"Identifier was already declared at current lexical level.",
									scanner.lineno()));
				}

				sym = new Symbol(*$1, TypeSymbol);

                                delete $1;

				table.addSymbol(sym);
			}
                        | IDENTIFIER ASSIGN type
                        { errorManager.addError(
                                new Error(InvalidTypeDecl,
                                          "Use \"=\" for type definitions.",
                                          scanner.lineno()));
                        
				Symbol* sym = table.getSymbolCurLevel(*$1);

				if (sym)
				{
					errorManager.addError(new Error(IdentifierInUse,
									"Identifier was already declared at current lexical level.",
									scanner.lineno()));
				}

				sym = new Symbol(*$1, TypeSymbol);

                                delete $1;

				table.addSymbol(sym);

			}
                        | error { ; }
                        ;

type                    : simple_type
			| enumerated_type
                        | structured_type
                        ;

simple_type             : IDENTIFIER
			{
				//TODO Make sure that this has been declared somewhere
			}
                        ;

enumerated_type		: LEFT_PAREN enum_list RIGHT_PAREN
			| LEFT_PAREN error RIGHT_PAREN
			{
                            errorManager.addError(
                                new Error(InvalidEnumDecl,
                                          "Invalid enumeration declaration.",
                                          scanner.lineno()));
                        }
			;

enum_list		: IDENTIFIER
			{
				Symbol* sym = table.getSymbolCurLevel(*$1);

				if (sym)
				{
					errorManager.addError(new Error(IdentifierInUse,
									"Identifier was already declared at current lexical level.",
									scanner.lineno()));
				}

				sym = new Symbol(*$1, TypeSymbol);

                                delete $1;

				table.addSymbol(sym);
			}
                        | enum_list COMMA IDENTIFIER
			{
				Symbol* sym = table.getSymbolCurLevel(*$3);

				if (sym)
				{
					errorManager.addError(new Error(IdentifierInUse,
									"Identifier was already declared at current lexical level.",
									scanner.lineno()));
				}

				sym = new Symbol(*$3, TypeSymbol);

                                delete $3;

				table.addSymbol(sym);
			}
                        ;

structured_type         : ARRAY LEFT_BRACKET index_type RIGHT_BRACKET OF type
                        | RECORD field_list END
                        | RECORD field_list SEMICOLON END
                        | RECORD error END
                        {
                            errorManager.addError(
                                new Error(InvalidRecordDecl,
                                          "Invalid record declaration.",
                                          scanner.lineno()));
                        }
                        | ARRAY error OF type
                        {
                            errorManager.addError(
                                new Error(InvalidArrayDecl,
                                          "Invalid array declaration.",
                                          scanner.lineno()));
                        }
                        ;

index_type              : simple_type
                        | type_expr UPTO type_expr
                        ;

field_list              : field
                        | field_list SEMICOLON field
                        ;

field                   : IDENTIFIER COLON type
			{
				//TODO Make sure that this hasn't been declared in the RECORD before
			}
			| IDENTIFIER COMMA field
			{
				//TODO Make sure that this hasn't been declared in the RECORD before
			}
			| IDENTIFIER error
			{
                            errorManager.addError(
                                new Error(InvalidRecordDecl,
                                          "Invalid field declaration.",
                                          scanner.lineno()));
                        }
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
			{
				Symbol* sym = table.getSymbolCurLevel(*$1);

				if (sym)
				{
					errorManager.addError(new Error(IdentifierInUse,
									"Identifier was already declared at current lexical level.",
									scanner.lineno()));
				}

				sym = new Symbol(*$1, TypeSymbol);

                                delete $1;

				table.addSymbol(sym);
			}
                        | IDENTIFIER COMMA var_decl
                        {
				Symbol* sym = table.getSymbolCurLevel(*$1);

				if (sym)
				{
					errorManager.addError(new Error(IdentifierInUse,
									"Identifier was already declared at current lexical level.",
									scanner.lineno()));
				}

				sym = new Symbol(*$1, TypeSymbol);

                                delete $1;

				table.addSymbol(sym);
			}
			| IDENTIFIER ASSIGN type
                        {
				Symbol* sym = table.getSymbolCurLevel(*$1);

				if (sym)
				{
					errorManager.addError(new Error(IdentifierInUse,
									"Identifier was already declared at current lexical level.",
									scanner.lineno()));
				}

				sym = new Symbol(*$1, TypeSymbol);

                                delete $1;

				table.addSymbol(sym);
				errorManager.addError(
                                new Error(InvalidVarDecl,
                                          "Use \":\" to declare variables.",
                                          scanner.lineno()));
                        }
                        | IDENTIFIER error
                        {
				Symbol* sym = table.getSymbolCurLevel(*$1);

				if (sym)
				{
					errorManager.addError(new Error(IdentifierInUse,
									"Identifier was already declared at current lexical level.",
									scanner.lineno()));
				}

				sym = new Symbol(*$1, TypeSymbol);

                                delete $1;

				table.addSymbol(sym);
				errorManager.addError(
                                new Error(InvalidVarDecl,
                                          "Use \":\" to declare variables.",
                                          scanner.lineno()));
              			errorManager.addError(
                                new Error(InvalidVarDecl,
                                          "Invalid variable declaration.",
                                          scanner.lineno()));
                        }
                        | error { ; }
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
                        | proc_heading decls compound_stat PERIOD
                        {
                          errorManager.addError(
                              new Error(InvalidProcDecl,
                                        "Funct/proc should not end with \".\".",
                                        scanner.lineno()));
                        }
                        ;

proc_heading            : PROCEDURE IDENTIFIER f_parm_decl SEMICOLON 
                        | FUNCTION IDENTIFIER f_parm_decl COLON IDENTIFIER SEMICOLON
                        | FUNCTION IDENTIFIER f_parm_decl SEMICOLON
                        {
                          errorManager.addError(
                              new Error(InvalidFunctDecl,
                                        "Function needs to return a value.",
                                        scanner.lineno()));
                        }
                        | PROCEDURE IDENTIFIER f_parm_decl COLON IDENTIFIER SEMICOLON
                        {
                          errorManager.addError(
                              new Error(InvalidProcDecl,
                                        "Procedure can't return a value.",
                                        scanner.lineno()));
                        }
                        | PROCEDURE error RIGHT_PAREN SEMICOLON
                        {
                          errorManager.addError(
                              new Error(InvalidProcDecl,
                                        "Invalid procedure header.",
                                        scanner.lineno()));
                        }

                        | FUNCTION error RIGHT_PAREN COLON IDENTIFIER SEMICOLON
                        {
                          errorManager.addError(
                              new Error(InvalidFunctDecl,
                                        "Invalid function header.",
                                        scanner.lineno()));
                        }
                        | error { ; }
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
                        | error { ; }
                        |
                        ;

simple_stat             : var ASSIGN expr
                        | proc_invok
                        | compound_stat
                        | var EQ expr 
                        {
                          errorManager.addError(
                              new Error(CStyleAssignment,
                                        "C-style assignment, expected \":=\".",
                                        scanner.lineno()));
                        }
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
			| /* empty */
                        ;

/********************************************************************************
 * Rules for expressions
 ********************************************************************************/

type_expr		: type_simple_expr
                        | type_expr EQ type_simple_expr
                        | type_expr NE type_simple_expr
                        | type_expr LE type_simple_expr
                        | type_expr LT type_simple_expr
                        | type_expr GE type_simple_expr
                        | type_expr GT type_simple_expr
                        ;

type_simple_expr        : type_term
                        | PLUS type_term
                        | MINUS type_term
                        | type_simple_expr PLUS type_term
                        | type_simple_expr MINUS type_term
                        | type_simple_expr OR  type_term
                        ;

type_term               : type_factor
                        | type_term MULTIPLY type_factor
                        | type_term REAL_DIVIDE type_factor
                        | type_term INT_DIVIDE type_factor
                        | type_term MOD type_factor
                        | type_term AND type_factor
                        ;

type_factor             : var
                        | LEFT_PAREN type_expr RIGHT_PAREN
                        | INT_CONST 
                        | NOT type_factor
                        ;


expr			: simple_expr
                        | expr EQ simple_expr
                        | expr NE simple_expr
                        | expr LE simple_expr
                        | expr LT simple_expr
                        | expr GE simple_expr
                        | expr GT simple_expr
                        ;

simple_expr             : term
                        | PLUS term
                        | MINUS term
                        | simple_expr PLUS term
                        | simple_expr MINUS term
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
                        | STRING_LITERAL
                        ;

unsigned_num            : INT_CONST
                        | REAL_CONST
                        ;


func_invok              : plist_finvok RIGHT_PAREN
                        | IDENTIFIER LEFT_PAREN RIGHT_PAREN
                        ;

%%

void print_error(const std::string msg)
{
	std::cerr << msg << std::endl;
}

// The most general error handling done here
void Meow::PalParser::error(const Meow::PalParser::location_type &loc, const std::string &msg)
{
	errorManager.addError(new Error(SyntaxError, msg, scanner.lineno()));
}

// Now that we have the Parser declared, we can declare the Scanner and implement
// the yylex function
#include "Scanner.hpp"
static int yylex(Meow::PalParser::semantic_type * yylval, Meow::PalScanner &scanner)
{
	return scanner.yylex(yylval);
}

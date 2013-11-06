%require "2.4.1"
%skeleton "lalr1.cc"
%defines
%define namespace "Meow"
%define parser_class_name "PalParser"
%parse-param { Meow::PalScanner &scanner }
%parse-param { Meow::ErrorManager &errorManager }
%parse-param { Meow::SymbolTable &table }
%parse-param { Meow::SemanticHelper &semanticHelper }
%lex-param   { Meow::PalScanner &scanner }
%lex-param   {Meow::SymbolTable &table  }

%debug
%error-verbose

%code requires {

 	#include <vector>

	// Forward-declare the Scanner class; the Parser needs to be assigned a 
	// Scanner, but the Scanner can't be declared without the Parser
	namespace Meow
	{
		class PalScanner;
		class ErrorManager;
		class SymbolTable;
		class SemanticHelper;
		class Type;
		class Symbol;
	}

	typedef std::pair<std::string*, Meow::Type*> IdTypePair;
	typedef std::vector<IdTypePair*> IdTypePairList;
}

%code {

 	#include "Scanner.hpp"

	#include "SemanticHelper.hpp"
	#include "ErrorManager.hpp"
	#include "Error.hpp"
 	#include "ErrorCodes.hpp"
 	#include "SymbolTable.hpp"

	#define YYDEBUG 1

	// Prototype for the yylex function
	static int yylex(Meow::PalParser::semantic_type * yylval, Meow::PalScanner &scanner,
			Meow::SymbolTable &table);
	void print_error(const std::string msg);
	void print_value(bool value);

	// Global counter for determining whether continue/exit are valid
	int g_whileCounter;
	int g_beginCounter;
}

%union {
	std::string* identifier;
        std::string* stringLiteral;

        std::vector<Symbol*>* symbolList;

        IdTypePair* idTypePair;
        IdTypePairList* idTypePairList;

        Type* type;
}

%type <type> var expr simple_expr term factor unsigned_const unsigned_num
%type <type> type simple_type enumerated_type structured_type var_decl 

%type <type> type_expr type_simple_expr type_term type_factor

%type <symbolList> enum_list

%type <idTypePair> field
%type <idTypePairList> field_list

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

				sym = new Symbol(*$1, Symbol::ConstantSymbol);

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

				sym = new Symbol(*$1, Symbol::ConstantSymbol);

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

				sym = new Symbol(*$1, Symbol::ConstantSymbol);

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

				sym = new Symbol(*$1, Symbol::ConstantSymbol);

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
				semanticHelper.defineType(*$1, $3);
                                delete $1;
			}
                        | IDENTIFIER ASSIGN type
                        { 
				errorManager.addError(
					new Error(InvalidTypeDecl,
						  "Use \"=\" for type definitions.",
						  scanner.lineno()));

				semanticHelper.defineType(*$1, $3);
                                delete $1;
			}
                        | error { ; }
                        ;

type                    : simple_type
			| enumerated_type
                        | structured_type
                        ;

simple_type             : IDENTIFIER
			{
				$$ = semanticHelper.getTypeFromID(*$1);
				delete $1;
			}
                        ;

enumerated_type		: LEFT_PAREN enum_list RIGHT_PAREN
			{
				$$ = new Type($2); // TODO when do we delete this? When type symbol goes out of scope?
							// (must differentiate from predefined types, or use refcounts)
			}
			| LEFT_PAREN error RIGHT_PAREN
			{
                            errorManager.addError(
                                new Error(InvalidEnumDecl,
                                          "Invalid enumeration declaration.",
                                          scanner.lineno()));
				// TODO int by default? or NULL?
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

				sym = new Symbol(*$1, Symbol::TypeSymbol);

                                delete $1;

				table.addSymbol(sym);
				
				$$ = new std::vector<Symbol*>();
				$$->push_back(sym);
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

				sym = new Symbol(*$3, Symbol::TypeSymbol);

                                delete $3;

				table.addSymbol(sym);

				$$ = $1;
				$$->push_back(sym);
			}
                        ;

structured_type         : ARRAY LEFT_BRACKET index_type RIGHT_BRACKET OF type
			{
				// return type with index type + element type
				$$ = new Type(NULL, $6); 
				// TODO detmine if indices matter at this point
				// (char array compatibility?)
			}
                        | RECORD field_list END
			{
				// TODO create a type, give it list of fields
				$$ = new Type($2);
				// TODO (use connor's pair list thing)?
			}
                        | RECORD field_list SEMICOLON END
			{
				// TODO create a type, give it list of fields
				$$ = new Type($2);
				// TODO (use connor's pair list thing)?
				// TODO both these rules are OK?
			}
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
                        {
				// actually need VALUES here!?
                        }
                        | type_expr UPTO type_expr
                        {
				// actually need VALUES here!?
                        }
                        ;

field_list              : field
			{
				$$ = new IdTypePairList();
				$$->push_back($1);
			}
                        | field_list SEMICOLON field
			{
				$$ = $1;
				// TODO check if id already used in field list	
				// might want to use (unordered) map instead of list to
				// avoid quadratic time!
				$$->push_back($3);
			}
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
                                semanticHelper.declareVariable(*$1, $3);
                                delete $1;
				$$ = $3;
			}
                        | IDENTIFIER COMMA var_decl
                        {
                                semanticHelper.declareVariable(*$1, $3);
                                delete $1;
				$$ = $3;
			}
			| IDENTIFIER ASSIGN type
                        {
                                semanticHelper.declareVariable(*$1, $3);
                                delete $1;
				$$ = $3;

				errorManager.addError(
					new Error(InvalidVarDecl,
						  "Use \":\" to declare variables.",
						  scanner.lineno()));
                        }
                        | IDENTIFIER error
                        {
				// TODO -- should we really do anything here?
                                semanticHelper.declareVariable(*$1, NULL);
                                delete $1;
                                $$ = NULL;

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
			{
				Symbol* sym = table.getSymbolCurLevel(*$2);

				if (sym)
				{
					errorManager.addError(new Error(IdentifierInUse,
									"Identifier was already declared at current lexical level.",
									scanner.lineno()));
				}

				sym = new Symbol(*$2, Symbol::ProcedureSymbol);

				table.addSymbol(sym);
				table.incLevel();
				
				sym = new Symbol(*$2, Symbol::ProcedureSymbol);

                                delete $2;

				table.addSymbol(sym);
			}
                        | FUNCTION IDENTIFIER f_parm_decl COLON IDENTIFIER SEMICOLON
			{
				Symbol* sym = table.getSymbolCurLevel(*$2);

				if (sym)
				{
					errorManager.addError(new Error(IdentifierInUse,
									"Identifier was already declared at current lexical level.",
									scanner.lineno()));
				}

				sym = new Symbol(*$2, Symbol::FunctionSymbol);

				table.addSymbol(sym);
				table.incLevel();
				
				sym = new Symbol(*$2, Symbol::FunctionSymbol);

                                delete $2;

				table.addSymbol(sym);
			}
                        | FUNCTION IDENTIFIER f_parm_decl SEMICOLON
                        {
				Symbol* sym = table.getSymbolCurLevel(*$2);

				if (sym)
				{
					errorManager.addError(new Error(IdentifierInUse,
									"Identifier was already declared at current lexical level.",
									scanner.lineno()));
				}

				sym = new Symbol(*$2, Symbol::FunctionSymbol);

				table.addSymbol(sym);
				table.incLevel();
				
				sym = new Symbol(*$2, Symbol::FunctionSymbol);

                                delete $2;

				table.addSymbol(sym);
                          	errorManager.addError(
                              	new Error(InvalidFunctDecl,
                                        "Function needs to return a value.",
                                        scanner.lineno()));
                        }
                        | PROCEDURE IDENTIFIER f_parm_decl COLON IDENTIFIER SEMICOLON
                        {
				Symbol* sym = table.getSymbolCurLevel(*$2);

				if (sym)
				{
					errorManager.addError(new Error(IdentifierInUse,
									"Identifier was already declared at current lexical level.",
									scanner.lineno()));
				}

				sym = new Symbol(*$2, Symbol::ProcedureSymbol);

				table.addSymbol(sym);
				table.incLevel();
				
				sym = new Symbol(*$2, Symbol::ProcedureSymbol);

                                delete $2;

				table.addSymbol(sym);
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
                        {
				$$ = semanticHelper.getTypeForVarId(*$1);
				delete $1;
                        }
                        | var PERIOD IDENTIFIER
                        {
                            // get symbol for $1.name
                            // get its type
                            // must be record!
                            // get record field corresponding to $3
                            // $$.type = fieldType
                        }
                        | subscripted_var RIGHT_BRACKET
                        {
                            // TODO -- i don't think this subscripted_var rule is right...
                            // it supports arrVar[1,2] for 2d array access...
                        }
                        ;

subscripted_var         : var LEFT_BRACKET expr
                        {
                        }
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
			{
				g_whileCounter--;
			}
                        | CONTINUE
                        | EXIT
                        ;

matched_stat            : simple_stat
                        | IF expr THEN matched_stat ELSE matched_stat
                        | WHILE expr DO matched_stat
			{
				g_whileCounter--;
			}
                        | CONTINUE
                        | EXIT
			| /* empty */
                        ;

/********************************************************************************
 * Rules for expressions
 ********************************************************************************/

type_expr		: type_simple_expr
                        {
                            $$ = $1;
                        }
                        | type_expr EQ type_simple_expr
                        {
                            Type* result = semanticHelper.getOpResultType(OpEQ, $1, $3);

                            if (result == NULL)
                            {
                                errorManager.addError(
                                    new Error(OperatorTypeMismatch,
                                        "Incompatible types for '='",
                                        scanner.lineno()));
                            }
                            
                            $$ = result;
                        }
                        | type_expr NE type_simple_expr
                        {
                            Type* result = semanticHelper.getOpResultType(OpNE, $1, $3);

                            if (result == NULL)
                            {
                                errorManager.addError(
                                    new Error(OperatorTypeMismatch,
                                        "Incompatible types for '<>'",
                                        scanner.lineno()));
                            }
                            
                            $$ = result;
                        }
                        | type_expr LE type_simple_expr
                        {
                            Type* result = semanticHelper.getOpResultType(OpLE, $1, $3);

                            if (result == NULL)
                            {
                                errorManager.addError(
                                    new Error(OperatorTypeMismatch,
                                        "Incompatible types for '<='",
                                        scanner.lineno()));
                            }
                            
                            $$ = result;
                        }
                        | type_expr LT type_simple_expr
                        {
                            Type* result = semanticHelper.getOpResultType(OpLT, $1, $3);

                            if (result == NULL)
                            {
                                errorManager.addError(
                                    new Error(OperatorTypeMismatch,
                                        "Incompatible types for '<'",
                                        scanner.lineno()));
                            }
                            
                            $$ = result;
                        }
                        | type_expr GE type_simple_expr
                        {
                            Type* result = semanticHelper.getOpResultType(OpGE, $1, $3);

                            if (result == NULL)
                            {
                                errorManager.addError(
                                    new Error(OperatorTypeMismatch,
                                        "Incompatible types for '>='",
                                        scanner.lineno()));
                            }
                            
                            $$ = result;
                        }
                        | type_expr GT type_simple_expr
                        {
                            Type* result = semanticHelper.getOpResultType(OpGT, $1, $3);

                            if (result == NULL)
                            {
                                errorManager.addError(
                                    new Error(OperatorTypeMismatch,
                                        "Incompatible types for '>'",
                                        scanner.lineno()));
                            }
                            
                            $$ = result;
                        }
                        ;

type_simple_expr        : type_term
                        {
                            $$ = $1;
                        }
                        | PLUS type_term
                        {
                            Type* result = semanticHelper.getOpResultType(OpPLUS, $2);

                            if (result == NULL)
                            {
                                errorManager.addError(
                                    new Error(OperatorTypeMismatch,
                                        "Incompatible type for unary '+'",
                                        scanner.lineno()));
                            }
                            
                            $$ = result;
                        }
                        | MINUS type_term
                        {
                            Type* result = semanticHelper.getOpResultType(OpMINUS, $2);

                            if (result == NULL)
                            {
                                errorManager.addError(
                                    new Error(OperatorTypeMismatch,
                                        "Incompatible type for unary '-'",
                                        scanner.lineno()));
                            }
                            
                            $$ = result;
                        }
                        | type_simple_expr PLUS type_term
                        {
                            Type* result = semanticHelper.getOpResultType(OpADD, $1, $3);

                            if (result == NULL)
                            {
                                errorManager.addError(
                                    new Error(OperatorTypeMismatch,
                                        "Incompatible types for '+'",
                                        scanner.lineno()));
                            }
                            
                            $$ = result;
                        }
                        | type_simple_expr MINUS type_term
                        {
                            Type* result = semanticHelper.getOpResultType(OpSUBTRACT, $1, $3);

                            if (result == NULL)
                            {
                                errorManager.addError(
                                    new Error(OperatorTypeMismatch,
                                        "Incompatible types for '-'",
                                        scanner.lineno()));
                            }
                            
                            $$ = result;
                        }
                        | type_simple_expr OR  type_term
                        {
                            Type* result = semanticHelper.getOpResultType(OpOR, $1, $3);

                            if (result == NULL)
                            {
                                errorManager.addError(
                                    new Error(OperatorTypeMismatch,
                                        "Incompatible types for 'or'",
                                        scanner.lineno()));
                            }
                            
                            $$ = result;
                        }
                        ;

type_term               : type_factor
                        {
                            $$ = $1;
                        }
                        | type_term MULTIPLY type_factor
                        {
                            Type* result = semanticHelper.getOpResultType(OpMULTIPLY, $1, $3);

                            if (result == NULL)
                            {
                                errorManager.addError(
                                    new Error(OperatorTypeMismatch,
                                        "Incompatible types for '*'",
                                        scanner.lineno()));
                            }
                            
                            $$ = result;
                        }
                        | type_term REAL_DIVIDE type_factor
                        {
                            Type* result = semanticHelper.getOpResultType(OpREALDIVIDE, $1, $3);

                            if (result == NULL)
                            {
                                errorManager.addError(
                                    new Error(OperatorTypeMismatch,
                                        "Incompatible types for '/'",
                                        scanner.lineno()));
                            }
                            
                            $$ = result;
                        }
                        | type_term INT_DIVIDE type_factor
                        {
                            Type* result = semanticHelper.getOpResultType(OpINTDIVIDE, $1, $3);

                            if (result == NULL)
                            {
                                errorManager.addError(
                                    new Error(OperatorTypeMismatch,
                                        "Incompatible types for 'div'",
                                        scanner.lineno()));
                            }
                            
                            $$ = result;
                        }
                        | type_term MOD type_factor
                        {
                            Type* result = semanticHelper.getOpResultType(OpMOD, $1, $3);

                            if (result == NULL)
                            {
                                errorManager.addError(
                                    new Error(OperatorTypeMismatch,
                                        "Incompatible types for 'mod'",
                                        scanner.lineno()));
                            }
                            
                            $$ = result;
                        }
                        | type_term AND type_factor
                        {
                            Type* result = semanticHelper.getOpResultType(OpAND, $1, $3);

                            if (result == NULL)
                            {
                                errorManager.addError(
                                    new Error(OperatorTypeMismatch,
                                        "Incompatible types for 'and'",
                                        scanner.lineno()));
                            }
                            
                            $$ = result;
                        }
                        ;

type_factor             : IDENTIFIER
			{
                            //$$ = $1;
				// TODO check that id is a constant?
			}
                        | LEFT_PAREN type_expr RIGHT_PAREN
                        {
                            $$ = $2;
                        }
                        | INT_CONST 
                        {
                            $$ = semanticHelper.getIntegerType();
                        }
                        | NOT type_factor
                        {
                            Type* result = semanticHelper.getOpResultType(OpNOT, $2);

                            if (result == NULL)
                            {
                                errorManager.addError(
                                    new Error(OperatorTypeMismatch,
                                        "Incompatible type for not.",
                                        scanner.lineno()));
                            }
                            
                            $$ = result;
                        }
                        ;


expr			: simple_expr
                        {
                            $$ = $1;
                        }
                        | expr EQ simple_expr
                        {
                            Type* result = semanticHelper.getOpResultType(OpEQ, $1, $3);

                            if (result == NULL)
                            {
                                errorManager.addError(
                                    new Error(OperatorTypeMismatch,
                                        "Incompatible types for '='",
                                        scanner.lineno()));
                            }
                            
                            $$ = result;
                        }
                        | expr NE simple_expr
                        {
                            Type* result = semanticHelper.getOpResultType(OpNE, $1, $3);

                            if (result == NULL)
                            {
                                errorManager.addError(
                                    new Error(OperatorTypeMismatch,
                                        "Incompatible types for '<>'",
                                        scanner.lineno()));
                            }
                            
                            $$ = result;
                        }
                        | expr LE simple_expr
                        {
                            Type* result = semanticHelper.getOpResultType(OpLE, $1, $3);

                            if (result == NULL)
                            {
                                errorManager.addError(
                                    new Error(OperatorTypeMismatch,
                                        "Incompatible types for '<='",
                                        scanner.lineno()));
                            }
                            
                            $$ = result;
                        }
                        | expr LT simple_expr
                        {
                            Type* result = semanticHelper.getOpResultType(OpLT, $1, $3);

                            if (result == NULL)
                            {
                                errorManager.addError(
                                    new Error(OperatorTypeMismatch,
                                        "Incompatible types for '<'",
                                        scanner.lineno()));
                            }
                            
                            $$ = result;
                        }
                        | expr GE simple_expr
                        {
                            Type* result = semanticHelper.getOpResultType(OpGE, $1, $3);

                            if (result == NULL)
                            {
                                errorManager.addError(
                                    new Error(OperatorTypeMismatch,
                                        "Incompatible types for '>='",
                                        scanner.lineno()));
                            }
                            
                            $$ = result;
                        }
                        | expr GT simple_expr
                        {
                            Type* result = semanticHelper.getOpResultType(OpGT, $1, $3);

                            if (result == NULL)
                            {
                                errorManager.addError(
                                    new Error(OperatorTypeMismatch,
                                        "Incompatible types for '>'",
                                        scanner.lineno()));
                            }
                            
                            $$ = result;
                        }
                        ;

simple_expr             : term
                        {
                            $$ = $1;
                        }
                        | PLUS term
                        {
                            Type* result = semanticHelper.getOpResultType(OpPLUS, $2);

                            if (result == NULL)
                            {
                                errorManager.addError(
                                    new Error(OperatorTypeMismatch,
                                        "Incompatible type for unary '+'",
                                        scanner.lineno()));
                            }
                            
                            $$ = result;
                        }
                        | MINUS term
                        {
                            Type* result = semanticHelper.getOpResultType(OpMINUS, $2);

                            if (result == NULL)
                            {
                                errorManager.addError(
                                    new Error(OperatorTypeMismatch,
                                        "Incompatible type for unary '-'",
                                        scanner.lineno()));
                            }
                            
                            $$ = result;
                        }
                        | simple_expr PLUS term
                        {
                            Type* result = semanticHelper.getOpResultType(OpADD, $1, $3);

                            if (result == NULL)
                            {
                                errorManager.addError(
                                    new Error(OperatorTypeMismatch,
                                        "Incompatible types for '+'",
                                        scanner.lineno()));
                            }
                            
                            $$ = result;
                        }
                        | simple_expr MINUS term
                        {
                            Type* result = semanticHelper.getOpResultType(OpSUBTRACT, $1, $3);

                            if (result == NULL)
                            {
                                errorManager.addError(
                                    new Error(OperatorTypeMismatch,
                                        "Incompatible types for '-'",
                                        scanner.lineno()));
                            }
                            
                            $$ = result;
                        }
                        | simple_expr OR term
                        {
                            Type* result = semanticHelper.getOpResultType(OpOR, $1, $3);

                            if (result == NULL)
                            {
                                errorManager.addError(
                                    new Error(OperatorTypeMismatch,
                                        "Incompatible types for 'or'",
                                        scanner.lineno()));
                            }
                            
                            $$ = result;
                        }
                        ;

term                    : factor
                        {
                            $$ = $1;
                        }
                        | term MULTIPLY factor
                        {
                            Type* result = semanticHelper.getOpResultType(OpMULTIPLY, $1, $3);

                            if (result == NULL)
                            {
                                errorManager.addError(
                                    new Error(OperatorTypeMismatch,
                                        "Incompatible types for '*'",
                                        scanner.lineno()));
                            }
                            
                            $$ = result;
                        }
                        | term REAL_DIVIDE factor
                        {
                            Type* result = semanticHelper.getOpResultType(OpREALDIVIDE, $1, $3);

                            if (result == NULL)
                            {
                                errorManager.addError(
                                    new Error(OperatorTypeMismatch,
                                        "Incompatible types for '/'",
                                        scanner.lineno()));
                            }
                            
                            $$ = result;
                        }
                        | term INT_DIVIDE factor
                        {
                            Type* result = semanticHelper.getOpResultType(OpINTDIVIDE, $1, $3);

                            if (result == NULL)
                            {
                                errorManager.addError(
                                    new Error(OperatorTypeMismatch,
                                        "Incompatible types for 'div'",
                                        scanner.lineno()));
                            }
                            
                            $$ = result;
                        }
                        | term MOD factor
                        {
                            Type* result = semanticHelper.getOpResultType(OpMOD, $1, $3);

                            if (result == NULL)
                            {
                                errorManager.addError(
                                    new Error(OperatorTypeMismatch,
                                        "Incompatible types for 'mod'",
                                        scanner.lineno()));
                            }
                            
                            $$ = result;
                        }
                        | term AND factor
                        {
                            Type* result = semanticHelper.getOpResultType(OpAND, $1, $3);

                            if (result == NULL)
                            {
                                errorManager.addError(
                                    new Error(OperatorTypeMismatch,
                                        "Incompatible types for 'and'",
                                        scanner.lineno()));
                            }
                            
                            $$ = result;
                        }
                        ;

factor                  : var
                        {
                            $$ = $1;
                        }
                        | unsigned_const
                        {
                            $$ = $1;
                        }
                        | LEFT_PAREN expr RIGHT_PAREN
                        {
                             $$ = $2;
                        }
                        | func_invok
                        {
                            // $$ = $1
                        }
                        | NOT factor
                        {
                            Type* result = semanticHelper.getOpResultType(OpNOT, $2);

                            if (result == NULL)
                            {
                                errorManager.addError(
                                    new Error(OperatorTypeMismatch,
                                        "Incompatible type for not.",
                                        scanner.lineno()));
                            }
                            
                            $$ = result;
                        }
                        ;

unsigned_const          : unsigned_num
                        {
                            $$ = $1;
                        }
                        | STRING_LITERAL
                        {
                            // $$.type = "string"
                        }
                        ;

unsigned_num            : INT_CONST
                        {
                            $$ = semanticHelper.getIntegerType();
                        }
                        | REAL_CONST
                        {
                            $$ = semanticHelper.getRealType();
                        }
                        ;


func_invok              : plist_finvok RIGHT_PAREN
                        {
                            // $$ = $1
                        }
                        | IDENTIFIER LEFT_PAREN RIGHT_PAREN
                        {
                            // get function for id
                            // verify it is defined
                            // $$.type = function return type
                        }
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
static int yylex(Meow::PalParser::semantic_type * yylval, Meow::PalScanner &scanner,
		Meow::SymbolTable &table)
{
	return scanner.yylex(yylval);
}

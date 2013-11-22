%require "2.4.1"
%skeleton "lalr1.cc"
%defines
%define namespace "Meow"
%define parser_class_name "PalParser"
%parse-param { Meow::PalScanner &scanner }
%parse-param { Meow::ErrorManager &errorManager }
%parse-param { Meow::SymbolTable &table }
%parse-param { Meow::SemanticHelper &semanticHelper }
%parse-param { Meow::AscHelper &ascHelper }
%lex-param   { Meow::PalScanner &scanner }
%lex-param   { Meow::SymbolTable &table  }

%debug
%error-verbose

%code requires 
{

 	#include <vector>
 	#include <string>

 	#include "Symbol.hpp"
	#include "SemanticHelper.hpp"
	#include "AscHelper.hpp"

	// Forward-declare the Scanner class; the Parser needs to be assigned a 
	// Scanner, but the Scanner can't be declared without the Parser
	
	#include "Symbol.hpp"

	namespace Meow
	{
		class PalScanner;
		class ErrorManager;
		class SymbolTable;
		class SemanticHelper;
		class Type;
		class Symbol;

		struct ArrayIndexRange;
	}
}

%code
{

 	#include <fstream>
 	#include "Scanner.hpp"

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
	int g_varOffset;
	vector<Meow::Symbol*> g_functionStack;
}

%initial-action
{
	g_whileCounter = 0;
	g_varOffset = 0;
	g_functionStack.clear();
}

%union
{
	int intConst;
        double realConst;

	std::string* identifier;
        std::string* stringLiteral;

        std::vector<Symbol*>* symbolList;

        IdTypePair* idTypePair;
        IdTypePairList* idTypePairList;

        FieldDecl fieldDecl;

        Meow::ConstExpr constExpr;
	ArrayIndexRange indexRange;

        Type* type;
        LValue lvalue;

	ParameterList* parameterList;
	Parameter* parameter;

	Meow::ProcedureInvocation procedureInvocation;
}

%type <type> unsigned_const unsigned_num
%type <type> type simple_type enumerated_type structured_type var_decl
%type <type> func_invok

%type <lvalue> parm expr simple_expr term factor

%type <lvalue> lhs_var lhs_subscripted_var
%type <lvalue> var subscripted_var

%type <constExpr> type_expr type_simple_expr type_term type_factor

%type <symbolList> enum_list

%type <idTypePair> field
%type <idTypePairList> field_list

%type <parameterList> f_parm_decl f_parm_list
%type <parameter> f_parm

%type <procedureInvocation> plist_finvok

%token <identifier> IDENTIFIER
%token <stringLiteral> STRING_LITERAL

%token <intConst> INT_CONST
%token <realConst> REAL_CONST

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
%%

program                 : program_head decls compound_stat PERIOD
			{
				// end of program
				ascHelper.out() << "\tSTOP" << endl;
			}
			| program_head decls compound_stat 
			{
				errorManager.addError(
					new Error(MissingProgramPeriod,
						"Expected \".\" after END", 
						scanner.lineno()-1)); 

				// end of program
				ascHelper.out() << "\tSTOP" << endl;
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
									"Identifier, '" + *$1 + "', was already declared at current lexical level.",
									scanner.lineno()));
				}

				sym = new Symbol(*$1, Symbol::ConstantSymbol);

				sym->setType($3.type);
				sym->setConstantValue($3.value);

                                delete $1;

				table.addSymbol(sym);
                        }
			| IDENTIFIER EQ STRING_LITERAL
                        {
				Symbol* sym = table.getSymbolCurLevel(*$1);

				if (sym)
				{
					errorManager.addError(new Error(IdentifierInUse,
									"Identifier, '" + *$1 + "', was already declared at current lexical level.",
									scanner.lineno()));
				}

				sym = new Symbol(*$1, Symbol::ConstantSymbol);

				sym->setType(new Type(*$3));
				
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
									"Identifier, '" + *$1 + "', was already declared at current lexical level.",
									scanner.lineno()));
				}

				sym = new Symbol(*$1, Symbol::ConstantSymbol);

				sym->setType($3.type);
				sym->setConstantValue($3.value);

                                delete $1;

				table.addSymbol(sym);
                        }
                        | IDENTIFIER error
                        {
                                errorManager.addError(
                                    new Error(InvalidConstDecl,
                                          "Invalid constant declaration for '" + *$1 + "'.",
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
				// TODO when do we delete this? When type symbol goes out of scope?
				// (must differentiate from predefined types, or use refcounts)
				$$ = new Type($2);
			}
			| LEFT_PAREN error RIGHT_PAREN
			{
                            errorManager.addError(
                                new Error(InvalidEnumDecl,
                                          "Invalid enumeration declaration.",
                                          scanner.lineno()));
				$$ = NULL;
                        }
			;

enum_list		: IDENTIFIER
			{
				Symbol* sym = table.getSymbolCurLevel(*$1);

				if (sym)
				{
					errorManager.addError(new Error(IdentifierInUse,
									"Identifier, '" + *$1 + "', was already declared at current lexical level.",
									scanner.lineno()));
				}

				sym = new Symbol(*$1, Symbol::ConstantSymbol);

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
									"Identifier, '" + *$3 + "', was already declared at current lexical level.",
									scanner.lineno()));
				}

				sym = new Symbol(*$3, Symbol::ConstantSymbol);

                                delete $3;

				table.addSymbol(sym);

				$$ = $1;
				$$->push_back(sym);
			}
                        ;

structured_type         : ARRAY LEFT_BRACKET type_expr UPTO type_expr RIGHT_BRACKET OF type
			{
				// TODO what kind of expresssions are actually allowed in type expr?
				$$ = semanticHelper.makeArrayType($3, $5, $8);
			}
			| ARRAY LEFT_BRACKET STRING_LITERAL UPTO STRING_LITERAL RIGHT_BRACKET OF type
			{
				ConstExpr start = {semanticHelper.getCharType(), {1}};
				ConstExpr end = {semanticHelper.getCharType(), {255}}; // arbitrary ...

				if ($3->size() != 1 || $5->size() != 1)
				{
					errorManager.addError(
						new Error(InvalidRecordDecl,
							  "Invalid expression in array index range.",
							  scanner.lineno()));
				}
				else
				{
					start.value.int_val = (int) $3->at(0);
					end.value.int_val = (int) $5->at(0);
				}

				$$ = semanticHelper.makeArrayType(start, end, $8);
			}
			| ARRAY LEFT_BRACKET simple_type RIGHT_BRACKET OF type
			{
				// array with typed index + element type
				$$ = semanticHelper.makeArrayType($3, $6);
			}
                        | RECORD field_list END
			{
				$$ = new Type($2);
			}
                        | RECORD field_list SEMICOLON END
			{
				$$ = new Type($2);
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

field_list              : field
			{
				$$ = new IdTypePairList();
				$$->push_back($1);
			}
                        | field_list SEMICOLON field
			{
				$$ = $1;
				semanticHelper.checkDuplicateField($1, $3);
				$$->push_back($3);
			}
                        ;

field                   : IDENTIFIER COLON type
			{
				$$ = new IdTypePair($1, $3);
			}
			| IDENTIFIER error
			{
				errorManager.addError(
					new Error(InvalidRecordDecl,
						  "Invalid field declaration for '" + *$1 + "'.",
						  scanner.lineno()));

				$$ = new IdTypePair($1, semanticHelper.getIntegerType());
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
			{
				// pop function/procedure off stack
				g_functionStack.pop_back();

				table.decLevel();
			}
                        | proc_heading decls compound_stat PERIOD
                        {
				// pop function/procedure off stack
				g_functionStack.pop_back();

				table.decLevel();
                          	errorManager.addError(
                              	new Error(InvalidProcDecl,
                                        "Funct/proc should not end with \".\".",
                                        scanner.lineno()));
                        }
                        ;

proc_heading            : PROCEDURE IDENTIFIER f_parm_decl SEMICOLON
			{
				Symbol* sym = table.getSymbolCurLevel(*$2);
				ParameterList* paramList;

				if (sym)
				{
					errorManager.addError(new Error(IdentifierInUse,
									"Identifier, '" + *$2 + "', was already declared at current lexical level.",
									scanner.lineno()));
				}

				paramList = $3;

				sym = new Symbol(*$2, Symbol::ProcedureSymbol);
				for (size_t i = 0; i < paramList->size(); i++)
				{
					sym->addParameter(paramList->at(i));
				}

				table.addSymbol(sym);
				table.incLevel();
				
				sym = new Symbol(*$2, Symbol::ProcedureSymbol);
				for (size_t i = 0; i < paramList->size(); i++)
				{
					sym->addParameter(paramList->at(i));
					semanticHelper.declareVariable(paramList->at(i).id, paramList->at(i).type);
				}

                                delete $2;

				table.addSymbol(sym);

				// push function/procedure onto stack
				g_functionStack.push_back(sym);
			}
                        | FUNCTION IDENTIFIER f_parm_decl COLON IDENTIFIER SEMICOLON
			{
				Symbol* sym = table.getSymbolCurLevel(*$2);
				ParameterList* paramList = NULL;
				Type * returnType;

				if (sym)
				{
					errorManager.addError(new Error(IdentifierInUse,
									"Identifier, '" + *$2 + "', was already declared at current lexical level.",
									scanner.lineno()));
				}

				paramList = $3;

				sym = new Symbol(*$2, Symbol::FunctionSymbol);
				for (size_t i = 0; i < paramList->size(); i++)
				{
					sym->addParameter(paramList->at(i));
				}
	
				
				returnType = semanticHelper.getTypeFromID(*$5);
                                
				sym->setType(returnType);

				table.addSymbol(sym);
				table.incLevel();
				
				sym = new Symbol(*$2, Symbol::FunctionSymbol);
				for (size_t i = 0; i < paramList->size(); i++)
				{
					sym->addParameter(paramList->at(i));
					semanticHelper.declareVariable(paramList->at(i).id, paramList->at(i).type);
				}

				delete $2;
				delete $5;

				sym->setType(returnType);
				table.addSymbol(sym);

				// push function/procedure onto stack
				g_functionStack.push_back(sym);
			}
                        | FUNCTION IDENTIFIER f_parm_decl SEMICOLON
                        {
				Symbol* sym = table.getSymbolCurLevel(*$2);
				ParameterList* paramList = NULL;

				if (sym)
				{
					errorManager.addError(new Error(IdentifierInUse,
									"Identifier, '" + *$2 + "', was already declared at current lexical level.",
									scanner.lineno()));
				}

				paramList = $3;

				sym = new Symbol(*$2, Symbol::FunctionSymbol);
				for (size_t i = 0; i < paramList->size(); i++)
				{
					sym->addParameter(paramList->at(i));
				}

				table.addSymbol(sym);
				table.incLevel();
				
				sym = new Symbol(*$2, Symbol::FunctionSymbol);
				for (size_t i = 0; i < paramList->size(); i++)
				{
					sym->addParameter(paramList->at(i));
					semanticHelper.declareVariable(paramList->at(i).id, paramList->at(i).type);
				}

                                delete $2;

				table.addSymbol(sym);

				// push function/procedure onto stack
				g_functionStack.push_back(sym);

                          	errorManager.addError(
                              	new Error(InvalidFunctDecl,
                                        "Function needs to return a value.",
                                        scanner.lineno()));
                        }
                        | PROCEDURE IDENTIFIER f_parm_decl COLON IDENTIFIER SEMICOLON
                        {
				Symbol* sym = table.getSymbolCurLevel(*$2);
				ParameterList* paramList = NULL;

				if (sym)
				{
					errorManager.addError(new Error(IdentifierInUse,
									"Identifier, '" + *$2 + "', was already declared at current lexical level.",
									scanner.lineno()));
				}

				paramList = $3;

				sym = new Symbol(*$2, Symbol::ProcedureSymbol);
				for (size_t i = 0; i < paramList->size(); i++)
				{
					sym->addParameter(paramList->at(i));
				}

				table.addSymbol(sym);
				table.incLevel();
				
				sym = new Symbol(*$2, Symbol::ProcedureSymbol);
				for (size_t i = 0; i < paramList->size(); i++)
				{
					sym->addParameter(paramList->at(i));
					semanticHelper.declareVariable(paramList->at(i).id, paramList->at(i).type);
				}

                                delete $2;

				table.addSymbol(sym);

				// push function/procedure onto stack
				g_functionStack.push_back(sym);

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

				// push dummy function/procedure onto stack
				Symbol sym;
				g_functionStack.push_back(&sym);
                        }

                        | FUNCTION error RIGHT_PAREN COLON IDENTIFIER SEMICOLON
                        {
                          errorManager.addError(
                              new Error(InvalidFunctDecl,
                                        "Invalid function header.",
                                        scanner.lineno()));

				// push dummy function/procedure onto stack
				Symbol sym;
				g_functionStack.push_back(&sym);
                        }
                        | error 
			{ 
				// push dummy function/procedure onto stack
				Symbol sym;
				g_functionStack.push_back(&sym);
			}
                        ;

f_parm_decl             : LEFT_PAREN f_parm_list RIGHT_PAREN
			{
			  $$ = $2;
			}
                        | LEFT_PAREN RIGHT_PAREN 
			{
			  $$ = new ParameterList();
			}
                        ;

f_parm_list             : f_parm
			{
			  $$ = new ParameterList();
			  $$->push_back(*$1);
			}
                        | f_parm_list SEMICOLON f_parm
			{
			  $$ = $1;
			  $$->push_back(*$3);
			}
                        ;

f_parm                  : IDENTIFIER COLON IDENTIFIER
			{
			  // just assume integer in case of error
			  Type* type = semanticHelper.getIntegerType();

			  Symbol* typeSymbol = table.getSymbol(*$3);
			  if (!typeSymbol)
			  {
				// Type not defined; Invoke error manager.
				errorManager.addError(
					new Error(SemanticError,
					"Undefined type, '" + *$1 + "'",
					scanner.lineno()));
			  }
			  else
			  {
				type = typeSymbol->getType();
			  }

			  $$ = new Parameter;
			  $$->id = *$1;
			  $$->type = type;
			  $$->var = false;
			}
                        | VAR IDENTIFIER COLON IDENTIFIER
			{
			  // just assume integer in case of error
			  Type* type = semanticHelper.getIntegerType();

			  Symbol* typeSymbol = table.getSymbol(*$4);
			  if (!typeSymbol)
			  {
				// Type not defined; Invoke error manager.
				errorManager.addError(
					new Error(SemanticError,
					"Undefined type, '" + *$2 + "'",
					scanner.lineno()));
			  }
			  else
			  {
				type = typeSymbol->getType();
			  }

			  $$ = new Parameter;
			  $$->id = *$2;
			  $$->type = type;
			  $$->var = true;

// TODO maybe idtypepair shouldn't hold a pointer to a string -- makes memory management trickier
			}
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

simple_stat             : lhs_var ASSIGN expr
			{
				if (!$1.assignable)
				{
					errorManager.addError(
						new Error(InvalidAssignment,
						"Cannot assign to value on left side of assignment statment.",
						scanner.lineno()));
				}
				else if (!semanticHelper.checkAssignmentCompatible($1.type, $3.type))
				{
					errorManager.addError(
						new Error(InvalidAssignment,
						"Non-assignment compatible types.",
						scanner.lineno()));
				}
			}
                        | proc_invok
                        | compound_stat
                        | lhs_var EQ expr 
                        {
				if (!$1.assignable)
				{
					errorManager.addError(
						new Error(InvalidAssignment,
						"Cannot assign to value on left side of assignment statment.",
						scanner.lineno()));
				}
				else if (!semanticHelper.checkAssignmentCompatible($1.type, $3.type))
				{
					errorManager.addError(
						new Error(InvalidAssignment,
						"Non-assignment compatible types.",
						scanner.lineno()));
				}
                          
			  	errorManager.addError(
                              	new Error(CStyleAssignment,
                                        "C-style assignment, expected \":=\".",
                                        scanner.lineno()));
                        }
                        ;

lhs_var                 : IDENTIFIER
                        {
				$$.type = semanticHelper.getTypeForVarId(*$1, $$.assignable, true, &g_functionStack);
				delete $1;
                        }
                        | lhs_var PERIOD IDENTIFIER
                        {
				$$.type = semanticHelper.getRecordFieldType($1.type, *$3, $$.assignable);
				delete $3;
                        }
                        | lhs_subscripted_var RIGHT_BRACKET
                        {
				$$ = $1;
                        }
                        ;

lhs_subscripted_var     : lhs_var LEFT_BRACKET expr
                        {
				$$.type = semanticHelper.getSubscriptedArrayType($1.type, $3.type, $$.assignable);
                        }
                        | lhs_subscripted_var COMMA expr
			{
				$$.type = semanticHelper.getSubscriptedArrayType($1.type, $3.type, $$.assignable);
			}
                        ;

var                     : IDENTIFIER
                        {
				$$.type = semanticHelper.getTypeForVarId(*$1, $$.assignable, false, &g_functionStack);
				delete $1;
                        }
                        | var PERIOD IDENTIFIER
                        {
				$$.type = semanticHelper.getRecordFieldType($1.type, *$3, $$.assignable);
				delete $3;
                        }
                        | subscripted_var RIGHT_BRACKET
                        {
				$$ = $1;
                        }
                        ;

subscripted_var         : var LEFT_BRACKET expr
                        {
				$$.type = semanticHelper.getSubscriptedArrayType($1.type, $3.type, $$.assignable);
                        }
                        | subscripted_var COMMA expr
			{
				$$.type = semanticHelper.getSubscriptedArrayType($1.type, $3.type, $$.assignable);
			}
                        ;

proc_invok              : plist_finvok RIGHT_PAREN
			{
				semanticHelper.checkProcedureInvocation(*$1.procedureName,
									$1.params);

				ascHelper.invokeProcedure(*$1.procedureName, $1.params);
				
				delete $1.params;
				delete $1.procedureName;
			}
                        | IDENTIFIER LEFT_PAREN RIGHT_PAREN
			{
				semanticHelper.checkProcedureInvocation(*$1, new InvocationParameters());

				delete $1;
			}
                        ;

plist_finvok            : IDENTIFIER LEFT_PAREN parm
			{
				$$.procedureName = $1;
				$$.params = new InvocationParameters();
				$$.params->push_back($3);
			}
                        | plist_finvok COMMA parm
			{
				$$ = $1;
				$$.params->push_back($3);
			}
                        ;

parm                    : expr
			{
				$$ = $1;
				// TODO argument value must be pushed onto stack 
				// (in correct order!)
			}

struct_stat             : IF expr THEN matched_stat ELSE stat
                        {
				semanticHelper.checkBoolean($2.type);
			}
			| IF expr THEN stat
			{
				semanticHelper.checkBoolean($2.type);
			}
                        | WHILE expr DO stat
			{
				semanticHelper.checkBoolean($2.type);
				g_whileCounter--;
			}
                        | CONTINUE
                        | EXIT
                        ;

matched_stat            : simple_stat
                        | IF expr THEN matched_stat ELSE matched_stat
                        {
				semanticHelper.checkBoolean($2.type);
			}
			| WHILE expr DO matched_stat
			{	
				semanticHelper.checkBoolean($2.type);
				g_whileCounter--;
			}
                        | CONTINUE
                        | EXIT
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
                            Type* result = semanticHelper.getOpResultType(OpEQ, $1.type, $3.type);

                            if (result == NULL)
                            {
                                errorManager.addError(
                                    new Error(OperatorTypeMismatch,
                                        "Incompatible types for '='",
                                        scanner.lineno()));
                            }

                            $$ = semanticHelper.getConstOpResult(OpEQ, $1, $3);
                        }
                        | type_expr NE type_simple_expr
                        {
                            Type* result = semanticHelper.getOpResultType(OpNE, $1.type, $3.type);

                            if (result == NULL)
                            {
                                errorManager.addError(
                                    new Error(OperatorTypeMismatch,
                                        "Incompatible types for '<>'",
                                        scanner.lineno()));
                            }
                            
                            $$ = semanticHelper.getConstOpResult(OpNE, $1, $3);
                        }
                        | type_expr LE type_simple_expr
                        {
                            Type* result = semanticHelper.getOpResultType(OpLE, $1.type, $3.type);

                            if (result == NULL)
                            {
                                errorManager.addError(
                                    new Error(OperatorTypeMismatch,
                                        "Incompatible types for '<='",
                                        scanner.lineno()));
                            }
                            
                            $$ = semanticHelper.getConstOpResult(OpLE, $1, $3);
                        }
                        | type_expr LT type_simple_expr
                        {
                            Type* result = semanticHelper.getOpResultType(OpLT, $1.type, $3.type);

                            if (result == NULL)
                            {
                                errorManager.addError(
                                    new Error(OperatorTypeMismatch,
                                        "Incompatible types for '<'",
                                        scanner.lineno()));
                            }
                            
                            $$ = semanticHelper.getConstOpResult(OpLT, $1, $3);
                        }
                        | type_expr GE type_simple_expr
                        {
                            Type* result = semanticHelper.getOpResultType(OpGE, $1.type, $3.type);

                            if (result == NULL)
                            {
                                errorManager.addError(
                                    new Error(OperatorTypeMismatch,
                                        "Incompatible types for '>='",
                                        scanner.lineno()));
                            }
                            
                            $$ = semanticHelper.getConstOpResult(OpGE, $1, $3);
                        }
                        | type_expr GT type_simple_expr
                        {
                            Type* result = semanticHelper.getOpResultType(OpGT, $1.type, $3.type);

                            if (result == NULL)
                            {
                                errorManager.addError(
                                    new Error(OperatorTypeMismatch,
                                        "Incompatible types for '>'",
                                        scanner.lineno()));
                            }
                            
                            $$ = semanticHelper.getConstOpResult(OpGT, $1, $3);
                        }
                        ;

type_simple_expr        : type_term
                        {
                            $$ = $1;
                        }
                        | PLUS type_term
                        {
                            Type* result = semanticHelper.getOpResultType(OpPLUS, $2.type);

                            if (result == NULL)
                            {
                                errorManager.addError(
                                    new Error(OperatorTypeMismatch,
                                        "Incompatible type for unary '+'",
                                        scanner.lineno()));
                            }
                            
                            $$ = semanticHelper.getConstOpResult(OpPLUS, $2);
                        }
                        | MINUS type_term
                        {
                            Type* result = semanticHelper.getOpResultType(OpMINUS, $2.type);

                            if (result == NULL)
                            {
                                errorManager.addError(
                                    new Error(OperatorTypeMismatch,
                                        "Incompatible type for unary '-'",
                                        scanner.lineno()));
                            }
                            
                            $$ = semanticHelper.getConstOpResult(OpMINUS, $2);
                        }
                        | type_simple_expr PLUS type_term
                        {
                            Type* result = semanticHelper.getOpResultType(OpADD, $1.type, $3.type);

                            if (result == NULL)
                            {
                                errorManager.addError(
                                    new Error(OperatorTypeMismatch,
                                        "Incompatible types for '+'",
                                        scanner.lineno()));
                            }
                            
                            $$ = semanticHelper.getConstOpResult(OpADD, $1, $3);
                        }
                        | type_simple_expr MINUS type_term
                        {
                            Type* result = semanticHelper.getOpResultType(OpSUBTRACT, $1.type, $3.type);

                            if (result == NULL)
                            {
                                errorManager.addError(
                                    new Error(OperatorTypeMismatch,
                                        "Incompatible types for '-'",
                                        scanner.lineno()));
                            }
                            
                            $$ = semanticHelper.getConstOpResult(OpSUBTRACT, $1, $3);
                        }
                        | type_simple_expr OR type_term
                        {
                            Type* result = semanticHelper.getOpResultType(OpOR, $1.type, $3.type);

                            if (result == NULL)
                            {
                                errorManager.addError(
                                    new Error(OperatorTypeMismatch,
                                        "Incompatible types for 'or'",
                                        scanner.lineno()));
                            }
                            
                            $$ = semanticHelper.getConstOpResult(OpOR, $1, $3);
                        }
                        ;

type_term               : type_factor
                        {
                            $$ = $1;
                        }
                        | type_term MULTIPLY type_factor
                        {
                            Type* result = semanticHelper.getOpResultType(OpMULTIPLY, $1.type, $3.type);

                            if (result == NULL)
                            {
                                errorManager.addError(
                                    new Error(OperatorTypeMismatch,
                                        "Incompatible types for '*'",
                                        scanner.lineno()));
                            }
                            
                            $$ = semanticHelper.getConstOpResult(OpMULTIPLY, $1, $3);
                        }
                        | type_term REAL_DIVIDE type_factor
                        {
                            Type* result = semanticHelper.getOpResultType(OpREALDIVIDE, $1.type, $3.type);

                            if (result == NULL)
                            {
                                errorManager.addError(
                                    new Error(OperatorTypeMismatch,
                                        "Incompatible types for '/'",
                                        scanner.lineno()));
                            }
                            
                            $$ = semanticHelper.getConstOpResult(OpREALDIVIDE, $1, $3);
                        }
                        | type_term INT_DIVIDE type_factor
                        {
                            Type* result = semanticHelper.getOpResultType(OpINTDIVIDE, $1.type, $3.type);

                            if (result == NULL)
                            {
                                errorManager.addError(
                                    new Error(OperatorTypeMismatch,
                                        "Incompatible types for 'div'",
                                        scanner.lineno()));
                            }
                            
                            $$ = semanticHelper.getConstOpResult(OpINTDIVIDE, $1, $3);
                        }
                        | type_term MOD type_factor
                        {
                            Type* result = semanticHelper.getOpResultType(OpMOD, $1.type, $3.type);

                            if (result == NULL)
                            {
                                errorManager.addError(
                                    new Error(OperatorTypeMismatch,
                                        "Incompatible types for 'mod'",
                                        scanner.lineno()));
                            }
                            
                            $$ = semanticHelper.getConstOpResult(OpMOD, $1, $3);
                        }
                        | type_term AND type_factor
                        {
                            Type* result = semanticHelper.getOpResultType(OpAND, $1.type, $3.type);

                            if (result == NULL)
                            {
                                errorManager.addError(
                                    new Error(OperatorTypeMismatch,
                                        "Incompatible types for 'and'",
                                        scanner.lineno()));
                            }
                            
                            $$ = semanticHelper.getConstOpResult(OpAND, $1, $3);
                        }
                        ;

type_factor             : IDENTIFIER
			{
				Symbol* symbol = semanticHelper.getSymbol(*$1);
				if (symbol == NULL || symbol->getSymbolType() != Symbol::ConstantSymbol)
				{
					errorManager.addError(new Error(SemanticError,
							"Identifer is not a constant.",
							scanner.lineno()));
					$$.type = semanticHelper.getIntegerType();
					$$.value.int_val = 0;
				}
				else
				{	
					$$.type = symbol->getType();
					$$.value = symbol->getConstantValue();
				}
				
				delete $1;
			}
                        | LEFT_PAREN type_expr RIGHT_PAREN
                        {
                            $$ = $2;
                        }
                        | INT_CONST 
                        {
                            $$.type = semanticHelper.getIntegerType();
                            $$.value.int_val = $1;
                        }
			| REAL_CONST
			{
				$$.type = semanticHelper.getRealType();
				$$.value.real_val = $1;
			}
                        | NOT type_factor
                        {
                            Type* result = semanticHelper.getOpResultType(OpNOT, $2.type);

                            if (result == NULL)
                            {
                                errorManager.addError(
                                    new Error(OperatorTypeMismatch,
                                        "Incompatible type for not.",
                                        scanner.lineno()));
                            }

                            $$ = semanticHelper.getConstOpResult(OpNOT, $2);
                        }
                        ;


expr			: simple_expr
                        {
                            $$ = $1;
                        }
                        | expr EQ simple_expr
                        {
                            Type* result = semanticHelper.getOpResultType(OpEQ, $1.type, $3.type);

                            if (result == NULL)
                            {
                                errorManager.addError(
                                    new Error(OperatorTypeMismatch,
                                        "Incompatible types for '='",
                                        scanner.lineno()));
                            }
                            
                            $$.type = result;
                            $$.assignable = false;
                        }
                        | expr NE simple_expr
                        {
                            Type* result = semanticHelper.getOpResultType(OpNE, $1.type, $3.type);

                            if (result == NULL)
                            {
                                errorManager.addError(
                                    new Error(OperatorTypeMismatch,
                                        "Incompatible types for '<>'",
                                        scanner.lineno()));
                            }
                            
                            $$.type = result;
                            $$.assignable = false;
                        }
                        | expr LE simple_expr
                        {
                            Type* result = semanticHelper.getOpResultType(OpLE, $1.type, $3.type);

                            if (result == NULL)
                            {
                                errorManager.addError(
                                    new Error(OperatorTypeMismatch,
                                        "Incompatible types for '<='",
                                        scanner.lineno()));
                            }
                            
                            $$.type = result;
                            $$.assignable = false;
                        }
                        | expr LT simple_expr
                        {
                            Type* result = semanticHelper.getOpResultType(OpLT, $1.type, $3.type);

                            if (result == NULL)
                            {
                                errorManager.addError(
                                    new Error(OperatorTypeMismatch,
                                        "Incompatible types for '<'",
                                        scanner.lineno()));
                            }
                            
                            $$.type = result;
                            $$.assignable = false;
                        }
                        | expr GE simple_expr
                        {
                            Type* result = semanticHelper.getOpResultType(OpGE, $1.type, $3.type);

                            if (result == NULL)
                            {
                                errorManager.addError(
                                    new Error(OperatorTypeMismatch,
                                        "Incompatible types for '>='",
                                        scanner.lineno()));
                            }
                            
                            $$.type = result;
                            $$.assignable = false;
                        }
                        | expr GT simple_expr
                        {
                            Type* result = semanticHelper.getOpResultType(OpGT, $1.type, $3.type);

                            if (result == NULL)
                            {
                                errorManager.addError(
                                    new Error(OperatorTypeMismatch,
                                        "Incompatible types for '>'",
                                        scanner.lineno()));
                            }
                            
                            $$.type = result;
                            $$.assignable = false;
                        }
                        ;

simple_expr             : term
                        {
                            $$ = $1;
                        }
                        | PLUS term
			{
				Type* result = semanticHelper.getOpResultType(OpPLUS, $2.type);

				if (result == NULL)
				{
					errorManager.addError(
						new Error(OperatorTypeMismatch,
							"Incompatible type for unary '+'",
							scanner.lineno()));
				}

				$$.type = result;
				$$.assignable = false;

				// noop
			}
                        | MINUS term
			{
				Type* result = semanticHelper.getOpResultType(OpMINUS, $2.type);

				if (result == NULL)
				{
					errorManager.addError(
						new Error(OperatorTypeMismatch,
							"Incompatible type for unary '-'",
							scanner.lineno()));
				}

				$$.type = result;
				$$.assignable = false;
				
				// negate value at top of stack
				if ($2.type == semanticHelper.getIntegerType())
				{
					// if integer ...
					ascHelper.out() << "\tCONSTI -1" << endl;
					ascHelper.out() << "\tMULI" << endl;
				}
				else
				{
					// if real ...
					ascHelper.out() << "\tCONSTR -1.0" << endl;
					ascHelper.out() << "\tMULR" << endl;
				}
			}
			| simple_expr PLUS term
			{
				Type* result = semanticHelper.getOpResultType(OpADD, $1.type, $3.type);

				if (result == NULL)
				{
					errorManager.addError(
						new Error(OperatorTypeMismatch,
							"Incompatible types for '+'",
							scanner.lineno()));
				}

				$$.type = result;
				$$.assignable = false;
				ascHelper.simpleExpressionHelper($1.type,$3.type, "ADD");

			}
			| simple_expr MINUS term
			{
				Type* result = semanticHelper.getOpResultType(OpSUBTRACT, $1.type, $3.type);

				if (result == NULL)
				{
					errorManager.addError(
						new Error(OperatorTypeMismatch,
							"Incompatible types for '-'",
							scanner.lineno()));
				}

				$$.type = result;
				$$.assignable = false;

				ascHelper.simpleExpressionHelper($1.type,$3.type, "SUB");
			}
			| simple_expr OR term
			{
				Type* result = semanticHelper.getOpResultType(OpOR, $1.type, $3.type);

				if (result == NULL)
				{
					errorManager.addError(
						new Error(OperatorTypeMismatch,
							"Incompatible types for 'or'",
							scanner.lineno()));
				}

				$$.type = result;
				$$.assignable = false;
			}
			;

term                    : factor
			{
				$$ = $1;
			}
			| term MULTIPLY factor
			{
				Type* result = semanticHelper.getOpResultType(OpMULTIPLY, $1.type, $3.type);

				if (result == NULL)
				{
					errorManager.addError(
						new Error(OperatorTypeMismatch,
							"Incompatible types for '*'",
							scanner.lineno()));
				}

				$$.type = result;
				$$.assignable = false;
				
				ascHelper.simpleExpressionHelper($1.type,$3.type, "MUL");
			}
			| term REAL_DIVIDE factor
			{
				Type* result = semanticHelper.getOpResultType(OpREALDIVIDE, $1.type, $3.type);

				if (result == NULL)
				{
					errorManager.addError(
						new Error(OperatorTypeMismatch,
							"Incompatible types for '/'",
							scanner.lineno()));
				}

				$$.type = result;
				$$.assignable = false;


				ascHelper.simpleExpressionHelper($1.type,$3.type, "DIV");
				ascHelper.out() << "\tIFERR division_zero" << endl;


			}
			| term INT_DIVIDE factor
			{
				Type* result = semanticHelper.getOpResultType(OpINTDIVIDE, $1.type, $3.type);

				if (result == NULL)
				{
					errorManager.addError(
						new Error(OperatorTypeMismatch,
							"Incompatible types for 'div'",
							scanner.lineno()));
				}

				$$.type = result;
				$$.assignable = false;
				
				ascHelper.simpleExpressionHelper($1.type,$3.type, "DIV");
				ascHelper.out() << "\tIFERR division_zero" << endl;
					
			}
			| term MOD factor
			{
				Type* result = semanticHelper.getOpResultType(OpMOD, $1.type, $3.type);

				if (result == NULL)
				{
					errorManager.addError(
						new Error(OperatorTypeMismatch,
							"Incompatible types for 'mod'",
							scanner.lineno()));
				}

				$$.type = result;
				$$.assignable = false;
			}
			| term AND factor
			{
				Type* result = semanticHelper.getOpResultType(OpAND, $1.type, $3.type);

				if (result == NULL)
				{
					errorManager.addError(
						new Error(OperatorTypeMismatch,
							"Incompatible types for 'and'",
							scanner.lineno()));
				}

				$$.type = result;
				$$.assignable = false;
			}
			;

factor                  : var
			{
				//$$.type = $1.type;
				$$ = $1;
			}
			| unsigned_const
			{
				$$.type = $1;
				$$.assignable = false;
			}
			| LEFT_PAREN expr RIGHT_PAREN
			{
				$$ = $2;
			}
			| func_invok
			{
				$$.type = $1;
				$$.assignable = false;
			}
			| NOT factor
			{
				Type* result = semanticHelper.getOpResultType(OpNOT, $2.type);

if (result == NULL)
				{
					errorManager.addError(
						new Error(OperatorTypeMismatch,
						"Incompatible type for not.",
						scanner.lineno()));
				}

				$$.type = result;
				$$.assignable = false;
			}
			;

unsigned_const          : unsigned_num
			{
				$$ = $1;
			}
			| STRING_LITERAL
			{
				$$ = new Type(*$1);
				// Do we put the string somewhere special somehow or 
				// just push it to stack here in place?
			}
			;

unsigned_num            : INT_CONST
			{
				$$ = semanticHelper.getIntegerType();
				ascHelper.out() << "\tCONSTI " << $1 << endl;
			}
			| REAL_CONST
			{
				$$ = semanticHelper.getRealType();
				ascHelper.out() << "\tCONSTR " << $1 << endl;
			}
			;


func_invok              : plist_finvok RIGHT_PAREN
			{
				$$ = semanticHelper.checkFunctionInvocation(*$1.procedureName,
									    $1.params);
				delete $1.procedureName;
			}
			| IDENTIFIER LEFT_PAREN RIGHT_PAREN
			{
				$$ = semanticHelper.checkFunctionInvocation(*$1, new InvocationParameters());
				delete $1;
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

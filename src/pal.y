%require "2.4.1"
%skeleton "lalr1.cc"
%defines
%define namespace "Meow"
%define parser_class_name "PalParser"
%parse-param { Meow::PalScanner &scanner }
%parse-param { Meow::ErrorManager &errorManager }
%parse-param { Meow::ParseResult &result }
%lex-param   { Meow::PalScanner &scanner }

%debug
%error-verbose

%code requires {

        #include "ASTNode.hpp"
        #include "Parser.hpp"

	// Forward-declare the Scanner class; the Parser needs to be assigned a 
	// Scanner, but the Scanner can't be declared without the Parser
	namespace Meow
	{
		class PalScanner;
		class ErrorManager;
	}
}

%code {
 	#include "Scanner.hpp"

	#include "ErrorManager.hpp"
	#include "Error.hpp"
 	#include "ErrorCodes.hpp"

	#define YYDEBUG 1

	// Prototype for the yylex function
	static int yylex(Meow::PalParser::semantic_type * yylval, Meow::PalScanner &scanner);
	void print_error(const std::string msg);
	void print_value(bool value);
}

%union {
	std::string* identifier;
        std::string* stringLiteral;

        // AST nodes...
/*
        Meow::Declarations* Declarations;

        Meow::ConstantDeclarationList* ConstantDeclarationList;
        Meow::TypeDeclarationList* TypeDeclarationList;
        Meow::VariableDeclarationList* VariableDeclarationList;
        Meow::ProcedureDeclarationList* ProcedureDeclarationList;

        Meow::ConstantDeclaration* ConstantDeclaration;
        Meow::TypeDeclaration* TypeDeclaration;
        Meow::VariableDeclaration* VariableDeclaration;
        Meow::ProcedureDeclaration* ProcedureDeclaration;

        Meow::StatementList* StatementList; // TODO remove
        Meow::CompoundStatement* CompundStatement;
        Meow::Statement* Statement;

        Meow::LValue* LValue;
*/
}

/*
%type <Declarations> decls

%type <ConstantDeclarationList> const_decl_part const_decl_list
%type <ConstantDeclaration> const_decl

%type <TypeDeclarationList> type_decl_part type_decl_list
%type <TypeDeclaration> type_decl

%type <VariableDeclarationList> var_decl_part var_decl_list
%type <VariableDeclaration> var_decl

%type <ProcedureDeclarationList> proc_decl_part proc_decl_list
%type <ProcedureDeclaration> proc_decl

%type <CompoundStatement> compound_stat stat_list
%type <Statement> stat simple_stat struct_stat proc_invok

%type <LValue> var
*/

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
                        {
                            //result.program = new Program($2, $3);
                        }
                        | program_head decls compound_stat 
                        { errorManager.addError(
                              new Error(MissingProgramPeriod,
                                        "Expected \".\" after END", 
                                        scanner.lineno()-1)); 
                            //result.program = new Program($2, $3);
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
                        {
                            //$$ = new Declarations($1, $2, $3, $4);
                        }
                        ;

/********************************************************************************
 * Rules for constant declarations...
 ********************************************************************************/
const_decl_part         : CONST const_decl_list SEMICOLON
                        {
                            //$$ = $2;
                        }
                        | /* empty */
                        {
                            //$$ = NULL;
                        }

                        ;

const_decl_list         : const_decl
                        {
                            //$$ = new ConstantDeclarationList(); 
                            //$$->push_back($1);
                        }
                        | const_decl_list SEMICOLON const_decl
                        {
                            //$$ = $1;
                            //$$->push_back($3);
                        }
                        ;

const_decl              : IDENTIFIER EQ type_expr
                        {
                            //$$ = new ConstantDeclaration(yylineno, $1, $3);
                        }
			| IDENTIFIER EQ STRING_LITERAL
                        {
                            //$$ = new ConstantDeclaration(yylineno, $1, $3);
                        }
			| IDENTIFIER EQ REAL_CONST
                        {
                            //Identifier id = new Identifier(yylineno, $1); // TODO move this to scanner?
                            //$$ = new ConstantDeclaration(yylineno, id, $3);
                        }
                        | IDENTIFIER ASSIGN type_expr
                        { errorManager.addError(
                                new Error(InvalidConstDecl,
                                          "Use \"=\" to assign constants.",
                                          scanner.lineno()));
                        }
                        | IDENTIFIER error
                        { errorManager.addError(
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
                        {
                            //$$ = $2;
                        }
                        | /* empty */
                        {
                            //$$ = NULL;
                        }
                        ;

type_decl_list          : type_decl
                        {
                            //$$ = new TypeDeclarationLIst() ;
                            //$$->push_back($1);
                        }
                        | type_decl_list SEMICOLON type_decl
                        {
                            //$$ = $1;
                            //$$->push_back($3);
                        }
                        ;

type_decl               : IDENTIFIER EQ type
                        | IDENTIFIER ASSIGN type
                        { errorManager.addError(
                                new Error(InvalidTypeDecl,
                                          "Use \"=\" for type definitions.",
                                          scanner.lineno()));
                        }
                        | error { ; }
                        ;

type                    : simple_type
			| enumerated_type
                        | structured_type
                        ;

simple_type             : IDENTIFIER
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
                        | enum_list COMMA IDENTIFIER
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
			| IDENTIFIER COMMA field
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
                        | IDENTIFIER COMMA var_decl
                        | IDENTIFIER ASSIGN type
                        {
                            errorManager.addError(
                                new Error(InvalidVarDecl,
                                          "Use \":\" to declare variables.",
                                          scanner.lineno()));
                        }
                        | IDENTIFIER error
                        {
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
                        {
                            //$$ = $1;
                        }
                        | /* empty */
                        {
                            //$$ = NULL;
                        }
                        ;

proc_decl_list          : proc_decl
                        {
                            //$$ = new ProcudureDeclarationList();
                            //$$->push_back($1);
                        }
                        | proc_decl_list proc_decl
                        {
                            //$$ = $1;
                            //$$->push_back($2);
                        }
                        ;

proc_decl               : proc_heading decls compound_stat SEMICOLON
                        {
                            //$$ = new ProcedureDeclaration(yylineno, procId, returnId, returnType, statement_list 
                            // NEED:
                            // linenumber
                            // procedure id
                            // parameter list
                            // if func: return type + id // COULD group last three into a node..
                            // declarations
                        }
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
                        {
                            //$$ = $2;
                        }
                        ;

stat_list               : stat
                        {
                            //$$ = new CompoundStatement();
                            //$$->addStatement($1);
                        }
                        | stat_list SEMICOLON stat
                        {
                            //$$ = $1;
                            //$$->addStatement($3);
                        }
                        ;

stat                    : simple_stat
                        | struct_stat
                        | error { ; }
                        |
                        ;

simple_stat             : var ASSIGN expr
                        {
                            //$$ = AssignStatement($1, $3);
                        }
                        | proc_invok
                        {
                            //$$ = $1;
                        }
                        | compound_stat
                        {
                            //$$ = $1;
                        }
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
                            //$$ = new Variable(yylineno, $1);
                        }
                        | var PERIOD IDENTIFIER
                        {
                            //$$ = new RecordField(yylineno, $1, $3);
                        }
/* NOTE: i don't think a[1,2] is actually valid for 2d array access... need to do a[1][2], right?
*/
                        | var LEFT_BRACKET expr RIGHT_BRACKET
                        {
                            //$$ = new SubscriptedVariable(yylineno, $1, $3);
                        }
                        ;

proc_invok              : IDENTIFIER args
                        {
                            //$$ = new ProcedureInvokation($1, $2);
                        }
                        ;

args                    : LEFT_PAREN RIGHT_PAREN
                        {
                            //$$ = new Arguments();
                        }
                        | LEFT_PAREN arg_list RIGHT_PAREN
                        {
                            //$$ = $2
                        }
                        ;

arg_list                : expr
                        {
                            //$$ = new Arguments();
                            //$$.addArg = $1;
                        }
                        | arg_list COMMA expr
                        {
                            //$$ = $1
                            //$$.addArg = $2;
                        }
                        ;

struct_stat             : IF expr THEN matched_stat ELSE stat
                        {
                            //$$ = new ConditionalStatement($2, $4, $6);
                        }
                        | IF expr THEN stat
                        {
                            //$$ = new ConditionalStatement($2, $4, NULL);
                        }
                        | WHILE expr DO stat
                        {
                            //$$ = new WhileStatement($2, $4);
                        }
                        | CONTINUE
                        {
                            //$$ = new ContinueStatment();
                        }
                        | EXIT
                        {
                            //$$ = new ExitStatement();
                        }
                        ;

matched_stat            : simple_stat
                        {
                            //$$ = $1;
                        }
                        | IF expr THEN matched_stat ELSE matched_stat
                        {
                            //$$ = new ConditionalStatement($2, $4, $6);
                        }
                        | WHILE expr DO matched_stat
                        {
                            //$$ = new WhileStatement($2, $4);
                        }
                        | CONTINUE
                        {
                            //$$ = new ContinueStatment();
                        }
                        | EXIT
                        {
                            //$$ = new ExitStatement();
                        }
			| /* empty */
                        {
                            //$$ = NULL // ??? should we have a 'NoOp' or something?
                        }
                        ;

/********************************************************************************
 * Rules for expressions
 ********************************************************************************/

type_expr		: type_simple_expr
                        | type_expr EQ type_simple_expr
                        {
                            //$$ = new EqualExpression($1, $3);
                            // C++11 .... maybe??
                            //$$ = new BinaryExpression<bool>([a,b] {return a == b;}, $1, $3);
                        }
                        | type_expr NE type_simple_expr
                        {
                            //$$ = new NotEqualExpression($1, $3);
                        }
                        | type_expr LE type_simple_expr
                        {
                            //$$ = new LessThanEqualExpression($1, $3);
                        }
                        | type_expr LT type_simple_expr
                        {
                            //$$ = new LessThanExpression($1, $3);
                        }
                        | type_expr GE type_simple_expr
                        {
                            //$$ = new GreaterThanEqualExpression($1, $3);
                        }
                        | type_expr GT type_simple_expr
                        {
                            //$$ = new GreaterThanExpression($1, $3);
                        }
                        ;

type_simple_expr        : type_term
                        | PLUS type_term
                        {
                            //$$ = new UnaryPlus($2);
                        }
                        | MINUS type_term
                        {
                            //$$ = new UnaryMinus($2);
                        }
                        | type_simple_expr PLUS type_term
                        {
                            //$$ = new AddExpression($2, $3);
                            // maybe ???
                            //$$ = new BinaryExpression([a,b] {return a + b;},$2, $3);
                        }
                        | type_simple_expr MINUS type_term
                        {
                            //$$ = new SubtractExpression($2, $3);
                        }
                        | type_simple_expr OR type_term
                        {
                            //$$ = new OrExpression($2, $3);
                        }
                        ;

type_term               : type_factor
                        | type_term MULTIPLY type_factor
                        {
                            //$$ = new MultiplyExpression($2, $3);
                        }
                        | type_term REAL_DIVIDE type_factor
                        {
                            //$$ = new RealDivideExpression($2, $3);
                        }
                        | type_term INT_DIVIDE type_factor
                        {
                            //$$ = new IntDivideExpression($2, $3);
                        }
                        | type_term MOD type_factor
                        {
                            //$$ = new ModExpression($2, $3);
                        }
                        | type_term AND type_factor
                        {
                            //$$ = new AndExpression($2, $3);
                        }
                        ;

type_factor             : var
                        | LEFT_PAREN type_expr RIGHT_PAREN
                        {
                            //$$ = $2;
                        }
                        | INT_CONST 
                        | NOT type_factor
                        {
                            //$$ = new NotExpression($2);
                        }
                        ;


expr			: simple_expr
                        | expr EQ simple_expr
                        {
                            //$$ = new EqualExpression($1, $3);
                            // C++11 .... maybe??
                            //$$ = new BinaryExpression<bool>([a,b] {return a == b;}, $1, $3);
                        }
                        | expr NE simple_expr
                        {
                            //$$ = new NotEqualExpression($1, $3);
                        }
                        | expr LE simple_expr
                        {
                            //$$ = new LessThanEqualExpression($1, $3);
                        }
                        | expr LT simple_expr
                        {
                            //$$ = new LessThanExpression($1, $3);
                        }
                        | expr GE simple_expr
                        {
                            //$$ = new GreaterThanEqualExpression($1, $3);
                        }
                        | expr GT simple_expr
                        {
                            //$$ = new GreaterThanExpression($1, $3);
                        }
                        ;

simple_expr             : term
                        | PLUS term
                        {
                            //$$ = new UnaryPlus($2);
                        }
                        | MINUS term
                        {
                            //$$ = new UnaryMinus($2);
                        }
                        | simple_expr PLUS term
                        {
                            //$$ = new AddExpression($2, $3);
                            // maybe ???
                            //$$ = new BinaryExpression([a,b] {return a + b;},$2, $3);
                        }
                        | simple_expr MINUS term
                        {
                            //$$ = new SubtractExpression($2, $3);
                        }
                        | simple_expr OR  term
                        {
                            //$$ = new OrExpression($2, $3);
                        }
                        ;

term                    : factor
                        | term MULTIPLY factor
                        {
                            //$$ = new MultiplyExpression($2, $3);
                        }
                        | term REAL_DIVIDE factor
                        {
                            //$$ = new RealDivideExpression($2, $3);
                        }
                        | term INT_DIVIDE factor
                        {
                            //$$ = new IntDivideExpression($2, $3);
                        }
                        | term MOD factor
                        {
                            //$$ = new ModExpression($2, $3);
                        }
                        | term AND factor
                        {
                            //$$ = new AndExpression($2, $3);
                        }
                        ;

factor                  : var
                        | unsigned_const
                        | LEFT_PAREN expr RIGHT_PAREN
                        {
                            //$$ = $2;
                        }
                        | func_invok
                        | NOT factor
                        {
                            //$$ = new NotExpression($2);
                        }
                        ;

unsigned_const          : unsigned_num
                        | STRING_LITERAL
                        ;

unsigned_num            : INT_CONST
                        | REAL_CONST
                        ;

func_invok              : IDENTIFIER args
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

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

        #include "Parser.hpp"
 	#include "AST.hpp"

	// Forward-declare the Scanner class; the Parser needs to be assigned a 
	// Scanner, but the Scanner can't be declared without the Parser
	namespace Meow
	{
		class PalScanner;
		class ErrorManager;
	}
}

%code {
        //debug
 	#include <iostream>

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
	Meow::Identifier* identifier;
	Meow::IntegerConstant* IntegerConstant;
	Meow::RealConstant* RealConstant;

        //std::string* stringLiteral;
        Meow::StringLiteral* StringLiteral;

        std::vector<Meow::Identifier*>* IdList;

        // AST nodes...
        Meow::Declarations* Declarations;
        Meow::CompoundStatement* CompoundStatement;

        Meow::ConstantDeclarationList* ConstantDeclarationList;
        Meow::TypeDeclarationList* TypeDeclarationList;
        Meow::VariableDeclarationList* VariableDeclarationList;
        Meow::ProcedureDeclarationList* ProcedureDeclarationList;

        Meow::ConstantDeclaration* ConstantDeclaration;
        Meow::TypeDeclaration* TypeDeclaration;
        Meow::VariableDeclaration* VariableDeclaration;
        Meow::ProcedureDeclaration* ProcedureDeclaration;
        Meow::ProcedureHeading* ProcedureHeading;
        Meow::ParameterList* ParameterList;
        Meow::Parameter* Parameter;

        Meow::Type* Type;
        Meow::ArrayIndex* ArrayIndex;
        Meow::Field* Field;
        Meow::FieldList* FieldList;

        Meow::Statement* Statement;
        Meow::Expression* Expression;

        Meow::Arguments* Arguments;

        Meow::LValue* LValue;
        Meow::Constant* Constant;
}

%type <Declarations> decls
%type <CompoundStatement> compound_stat stat_list

%type <ConstantDeclarationList> const_decl_part const_decl_list
%type <ConstantDeclaration> const_decl

%type <TypeDeclarationList> type_decl_part type_decl_list
%type <TypeDeclaration> type_decl
%type <Type> type simple_type enumerated_type structured_type
%type <IdList> enum_list
%type <ArrayIndex> index_type

%type <FieldList> field_list
%type <Field> field

%type <VariableDeclarationList> var_decl_part var_decl_list
%type <VariableDeclaration> var_decl

%type <ProcedureDeclarationList> proc_decl_part proc_decl_list
%type <ProcedureDeclaration> proc_decl
%type <ProcedureHeading> proc_heading
%type <ParameterList> f_parm_decl f_parm_list
%type <Parameter> f_parm

%type <Statement> stat simple_stat struct_stat proc_invok matched_stat
%type <Expression> expr type_expr simple_expr type_simple_expr term type_term factor type_factor func_invok

%type <Arguments> args arg_list

%type <LValue> var


%token <identifier> IDENTIFIER

%type <Constant> unsigned_const unsigned_num

%token <StringLiteral> STRING_LITERAL
%token <IntegerConstant> INT_CONST
%token <RealConstant> REAL_CONST

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
                            result.program = new Program($2, $3);
                        }
                        | program_head decls compound_stat 
                        { errorManager.addError(
                              new Error(MissingProgramPeriod,
                                        "Expected \".\" after END", 
                                        scanner.lineno()-1)); 
                            result.program = new Program($2, $3);
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
                            $$ = new Declarations($1, $2, $3, $4);
                        }
                        ;

/********************************************************************************
 * Rules for constant declarations...
 ********************************************************************************/
const_decl_part         : CONST const_decl_list SEMICOLON
                        {
                            $$ = $2;
                        }
                        | /* empty */
                        {
                            $$ = NULL;
                        }

                        ;

const_decl_list         : const_decl
                        {
                            $$ = new ConstantDeclarationList(); 
                            $$->push_back($1);
                        }
                        | const_decl_list SEMICOLON const_decl
                        {
                            $$ = $1;
                            $$->push_back($3);
                        }
                        ;

const_decl              : IDENTIFIER EQ type_expr
                        {
                            $$ = new ConstantDeclaration(scanner.lineno(), $1, $3);
                        }
			| IDENTIFIER EQ STRING_LITERAL
                        {
                            $$ = new ConstantDeclaration(scanner.lineno(), $1, new Expression($3));
                        }
			| IDENTIFIER EQ REAL_CONST
                        {
                            $$ = new ConstantDeclaration(scanner.lineno(), $1, new Expression($3));
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
                            $$ = $2;
                        }
                        | /* empty */
                        {
                            $$ = NULL;
                        }
                        ;

type_decl_list          : type_decl
                        {
                            $$ = new TypeDeclarationList();
                            $$->push_back($1);
                        }
                        | type_decl_list SEMICOLON type_decl
                        {
                            $$ = $1;
                            $$->push_back($3);
                        }
                        ;

type_decl               : IDENTIFIER EQ type
                        {
                            $$ = new TypeDeclaration(scanner.lineno(), $1, $3);
                        }
                        | IDENTIFIER ASSIGN type
                        {   
                            errorManager.addError(
                                new Error(InvalidTypeDecl,
                                          "Use \"=\" for type definitions.",
                                          scanner.lineno()));

                            $$ = new TypeDeclaration(scanner.lineno(), $1, $3);
                        }
                        | error { ; }
                        ;

type                    : simple_type
			| enumerated_type
                        | structured_type
                        ;

simple_type             : IDENTIFIER
                        {
                            $$ = new SimpleType($1);
                        }
                        ;

enumerated_type		: LEFT_PAREN enum_list RIGHT_PAREN
                        {
                            $$ = new EnumeratedType($2);
                        }
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
                            $$ = new std::vector<Identifier*>();
                            $$->push_back($1);
                        }
                        | enum_list COMMA IDENTIFIER
                        {
                            $$ = $1;
                            $$->push_back($3);
                        }
                        ;

structured_type         : ARRAY LEFT_BRACKET index_type RIGHT_BRACKET OF type
                        {
                            $$ = new ArrayType($3, $6);
                        }
                        | RECORD field_list END
                        {
                            $$ = new RecordType($2);
                        }
                        | RECORD field_list SEMICOLON END
                        {
                            $$ = new RecordType($2);
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
                            $$ = new ArrayTypeIndex($1);
                        }
                        | type_expr UPTO type_expr
                        {
                            $$ = new ArrayRangeIndex($1, $3);
                        }
                        ;

field_list              : field
                        {
                            $$ = new FieldList();
                            $$->push_back($1);
                        }
                        | field_list SEMICOLON field
                        {
                            $$ = $1;
                            $$->push_back($3);
                        }
                        ;

field                   : IDENTIFIER COLON type
                        {
                            $$ = new Field(scanner.lineno(), $3);
                            $$->addIdentifier($1);
                        }
			| IDENTIFIER COMMA field 
                        {
                            // FIXME - right recursive rule!
                            $$ = $3;
                            $$->addIdentifier($1);
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
                        {
                            $$ = $2;
                        }
                        | /* empty */
                        {
                            $$ = NULL;
                        }
                        ;

var_decl_list           : var_decl
                        {
                            $$ = new VariableDeclarationList(); 
                            $$->push_back($1);
                        }
                        | var_decl_list SEMICOLON var_decl
                        {
                            $$ = $1;
                            $$->push_back($3);
                        }
                        ;

var_decl                : IDENTIFIER COLON type
                        {
                            $$ = new VariableDeclaration(scanner.lineno(), $3);

                            $$->addIdentifier($1);
                        }
                        | IDENTIFIER COMMA var_decl
                        {
                            $$ = $3;
                            $$->addIdentifier($1);
                        }
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
                            $$ = $1;
                        }
                        | /* empty */
                        {
                            $$ = NULL;
                        }
                        ;

proc_decl_list          : proc_decl
                        {
                            $$ = new ProcedureDeclarationList();
                            $$->push_back($1);
                        }
                        | proc_decl_list proc_decl
                        {
                            $$ = $1;
                            $$->push_back($2);
                        }
                        ;

proc_decl               : proc_heading decls compound_stat SEMICOLON
                        {
                            $$ = new ProcedureDeclaration(scanner.lineno(), $1, $2, $3);
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
                        {
                            $$ = new ProcedureHeading(scanner.lineno(), $2, $3, NULL);
                        }
                        | FUNCTION IDENTIFIER f_parm_decl COLON IDENTIFIER SEMICOLON
                        {
                            $$ = new ProcedureHeading(scanner.lineno(), $2, $3, $5);
                        }
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
                        {
                            $$ = $2;
                        }
                        | LEFT_PAREN RIGHT_PAREN 
                        {
                            $$ = new ParameterList(scanner.lineno());
                        }

                        ;

f_parm_list             : f_parm
                        {
                            $$ = new ParameterList(scanner.lineno());
                            $$->addParameter($1);
                        }
                        | f_parm_list SEMICOLON f_parm
                        {
                            $$ = $1;
                            $$->addParameter($3);
                        }
                        ;

f_parm                  : IDENTIFIER COLON IDENTIFIER
                        {
                            $$ = new Parameter(scanner.lineno(), $1, $3, false);
                        }
                        | VAR IDENTIFIER COLON IDENTIFIER
                        {
                            $$ = new Parameter(scanner.lineno(), $2, $4, true);
                        }
                        ;

/********************************************************************************
 * Rules for statements
 ********************************************************************************/

compound_stat           : PAL_BEGIN stat_list END
                        {
                            $$ = $2;
                        }
                        ;

stat_list               : stat
                        {
                            $$ = new CompoundStatement();
                            if ($1)
                            { 
                                $$->addStatement($1);
                            }
                        }
                        | stat_list SEMICOLON stat
                        {
                            $$ = $1;
                            if ($3)
                            { 
                                $$->addStatement($3);
                            }
                        }
                        ;

stat                    : simple_stat
                        | struct_stat
                        | error { ; }
                        | /* empty */ { $$ = NULL; }
                        ;

simple_stat             : var ASSIGN expr
                        {
                            $$ = new AssignStatement($1, $3);
                        }
                        | proc_invok
                        {
                            $$ = $1;
                        }
                        | compound_stat
                        {
                            $$ = $1;
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
                            $$ = new Variable(scanner.lineno(), $1);
                        }
                        | var PERIOD IDENTIFIER
                        {
                            $$ = new RecordField(scanner.lineno(), $1, $3);
                        }
/* NOTE: i don't think a[1,2] is actually valid for 2d array access... need to do a[1][2], right?
*/
                        | var LEFT_BRACKET expr RIGHT_BRACKET
                        {
                            $$ = new SubscriptedVariable(scanner.lineno(), $1, $3);
                        }
                        ;

proc_invok              : IDENTIFIER args
                        {
                            $$ = new ProcedureInvocation($1, $2);
                        }
                        ;

args                    : LEFT_PAREN RIGHT_PAREN
                        {
                            $$ = new Arguments(); // TODO or just null?
                        }
                        | LEFT_PAREN arg_list RIGHT_PAREN
                        {
                            $$ = $2;
                        }
                        ;

arg_list                : expr
                        {
                            $$ = new Arguments();
                            $$->addArgument($1);
                        }
                        | arg_list COMMA expr
                        {
                            $$ = $1;
                            $$->addArgument($3);
                        }
                        ;

struct_stat             : IF expr THEN matched_stat ELSE stat
                        {
                            $$ = new ConditionalStatement($2, $4, $6);
                        }
                        | IF expr THEN stat
                        {
                            $$ = new ConditionalStatement($2, $4, NULL);
                        }
                        | WHILE expr DO stat
                        {
                            $$ = new WhileStatement($2, $4);
                        }
                        | CONTINUE
                        {
                            $$ = new ContinueStatement();
                        }
                        | EXIT
                        {
                            $$ = new ExitStatement();
                        }
                        ;

matched_stat            : simple_stat
                        {
                            $$ = $1;
                        }
                        | IF expr THEN matched_stat ELSE matched_stat
                        {
                            $$ = new ConditionalStatement($2, $4, $6);
                        }
                        | WHILE expr DO matched_stat
                        {
                            $$ = new WhileStatement($2, $4);
                        }
                        | CONTINUE
                        {
                            $$ = new ContinueStatement();
                        }
                        | EXIT
                        {
                            $$ = new ExitStatement();
                        }
			| /* empty */
                        {
                            $$ = NULL; // ??? should we have a 'NoOp' or something?
                        }
                        ;

/********************************************************************************
 * Rules for expressions
 ********************************************************************************/

type_expr		: type_simple_expr
                        | type_expr EQ type_simple_expr
                        {
                            $$ = new EqualExpression($1, $3);
                        }
                        | type_expr NE type_simple_expr
                        {
                            $$ = new NotEqualExpression($1, $3);
                        }
                        | type_expr LE type_simple_expr
                        {
                            $$ = new LessThanEqualExpression($1, $3);
                        }
                        | type_expr LT type_simple_expr
                        {
                            $$ = new LessThanExpression($1, $3);
                        }
                        | type_expr GE type_simple_expr
                        {
                            $$ = new GreaterThanEqualExpression($1, $3);
                        }
                        | type_expr GT type_simple_expr
                        {
                            $$ = new GreaterThanExpression($1, $3);
                        }
                        ;

type_simple_expr        : type_term
                        | PLUS type_term
                        {
                            $$ = new UnaryPlusExpression($2);
                        }
                        | MINUS type_term
                        {
                            $$ = new UnaryMinusExpression($2);
                        }
                        | type_simple_expr PLUS type_term
                        {
                            $$ = new AddExpression($1, $3);
                        }
                        | type_simple_expr MINUS type_term
                        {
                            $$ = new SubtractExpression($1, $3);
                        }
                        | type_simple_expr OR type_term
                        {
                            $$ = new OrExpression($1, $3);
                        }
                        ;

type_term               : type_factor
                        | type_term MULTIPLY type_factor
                        {
                            $$ = new MultiplyExpression($1, $3);
                        }
                        | type_term REAL_DIVIDE type_factor
                        {
                            $$ = new RealDivideExpression($1, $3);
                        }
                        | type_term INT_DIVIDE type_factor
                        {
                            $$ = new IntDivideExpression($1, $3);
                        }
                        | type_term MOD type_factor
                        {
                            $$ = new ModExpression($1, $3);
                        }
                        | type_term AND type_factor
                        {
                            $$ = new AndExpression($1, $3);
                        }
                        ;

type_factor             : var
                        {
                            $$ = new Expression($1);
                        }
                        | LEFT_PAREN type_expr RIGHT_PAREN
                        {
                            $$ = $2;
                        }
                        | INT_CONST 
                        {
                            $$ = new Expression($1);
                        }
                        | NOT type_factor
                        {
                            $$ = new NotExpression($2);
                        }
                        ;


expr			: simple_expr
                        | expr EQ simple_expr
                        {
                            $$ = new EqualExpression($1, $3);
                        }
                        | expr NE simple_expr
                        {
                            $$ = new NotEqualExpression($1, $3);
                        }
                        | expr LE simple_expr
                        {
                            $$ = new LessThanEqualExpression($1, $3);
                        }
                        | expr LT simple_expr
                        {
                            $$ = new LessThanExpression($1, $3);
                        }
                        | expr GE simple_expr
                        {
                            $$ = new GreaterThanEqualExpression($1, $3);
                        }
                        | expr GT simple_expr
                        {
                            $$ = new GreaterThanExpression($1, $3);
                        }
                        ;

simple_expr             : term
                        | PLUS term
                        {
                            $$ = new UnaryPlusExpression($2);
                        }
                        | MINUS term
                        {
                            $$ = new UnaryMinusExpression($2);
                        }
                        | simple_expr PLUS term
                        {
                            $$ = new AddExpression($1, $3);
                        }
                        | simple_expr MINUS term
                        {
                            $$ = new SubtractExpression($1, $3);
                        }
                        | simple_expr OR term
                        {
                            $$ = new OrExpression($1, $3);
                        }
                        ;

term                    : factor
                        | term MULTIPLY factor
                        {
                            $$ = new MultiplyExpression($1, $3);
                        }
                        | term REAL_DIVIDE factor
                        {
                            $$ = new RealDivideExpression($1, $3);
                        }
                        | term INT_DIVIDE factor
                        {
                            $$ = new IntDivideExpression($1, $3);
                        }
                        | term MOD factor
                        {
                            $$ = new ModExpression($1, $3);
                        }
                        | term AND factor
                        {
                            $$ = new AndExpression($1, $3);
                        }
                        ;

factor                  : var
                        {
                            $$ = new Expression($1);
                        }
                        | unsigned_const
                        {
                            // FIXME ...
                            //$$ = new Expression($1);
                        }
                        | LEFT_PAREN expr RIGHT_PAREN
                        {
                            $$ = $2;
                        }
                        | func_invok
                        | NOT factor
                        {
                            $$ = new NotExpression($2);
                        }
                        ;

unsigned_const          : unsigned_num
                        {
                            $$ = $1;
                        }
                        | STRING_LITERAL
                        {
                            $$ = $1;
                        }
                        ;

unsigned_num            : INT_CONST
                        {
                            $$ = $1;
                        }
                        | REAL_CONST
                        {
                            $$ = $1;
                        }
                        ;

func_invok              : IDENTIFIER args
                        {
                            $$ = new FunctionInvocation($1, $2);
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
static int yylex(Meow::PalParser::semantic_type * yylval, Meow::PalScanner &scanner)
{
	return scanner.yylex(yylval);
}

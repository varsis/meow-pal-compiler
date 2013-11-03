#include "gtest/gtest.h"

#include "../src/pal.tab.hpp"
#include "../src/Scanner.hpp"
#include "../src/Parser.hpp"
#include "../src/ErrorManager.hpp"
#include "../src/Error.hpp"

#include "../src/AST.hpp"

#include "MockScanner.h"

using namespace std;

namespace Meow
{
	typedef PalParser::token token;
	typedef PalParser::token_type token_type;

	enum ParseRetval
	{
		Success = 0,
		Failure = 1
	};

	class ASTTest : public ::testing::Test
	{
		protected:

			ASTTest() 
				: parser(&errorManager)
			{
			}

			virtual void SetUp()
			{
			}

			virtual void TearDown()
			{
			}

			int expectedParseResult;

			ErrorManager errorManager;
			Parser parser;
	};

	TEST_F(ASTTest, TestMinimalAST)
	{
		int retval = parser.parseFile("test/test_cases/vtMinimalProgram.pal");
		ASSERT_EQ(0, retval);

		// verify AST
		ParseResult* result = parser.getParseResult();
		ASSERT_NE((ParseResult*)(NULL), result);
		ASSERT_NE((Program*)(NULL), result->program);

		// TODO could we do this with a visitor?

		ASSERT_NE((Program*)(NULL), result->program);
		ASSERT_EQ((CompoundStatement*)(NULL), result->program->getStatements());
	}

	TEST_F(ASTTest, TestASTConstDecls)
	{
		int retval = parser.parseFile("test/test_cases/vtBasicProgram0.pal");
		ASSERT_EQ(0, retval);

		ParseResult* result = parser.getParseResult();
		ASSERT_NE((ParseResult*)(NULL), result);
		ASSERT_NE((Program*)(NULL), result->program);

		Program* program = result->program;
		ASSERT_NE((Program*)(NULL), program);

		const Declarations* decls = program->getDeclarations();
		ASSERT_NE((Declarations*)(NULL), decls);

		const ConstantDeclarationList* consts = decls->getConstantDeclarationList();
		ASSERT_NE((ConstantDeclarationList*)(NULL), consts);
		ASSERT_EQ(1u, consts->size());

		ConstantDeclaration* decl = consts->at(0);
		ASSERT_EQ("theAnswer", decl->getIdentifier()->toString());
	}

	TEST_F(ASTTest, TestASTVarDecls)
	{
		int retval = parser.parseFile("test/test_cases/vtBasicProgram0.pal");
		ASSERT_EQ(0, retval);

		ParseResult* result = parser.getParseResult();
		ASSERT_NE((ParseResult*)(NULL), result);
		ASSERT_NE((Program*)(NULL), result->program);

		Program* program = result->program;
		ASSERT_NE((Program*)(NULL), program);

		const Declarations* decls = program->getDeclarations();
		ASSERT_NE((Declarations*)(NULL), decls);

		const VariableDeclarationList* vars = decls->getVariableDeclarationList();
		ASSERT_NE((VariableDeclarationList*)(NULL), vars);
		ASSERT_EQ(1u, vars->size());

		VariableDeclaration* decl = vars->at(0);
		ASSERT_EQ(1u, decl->getIdentifiers()->size());
		ASSERT_EQ("number", decl->getIdentifiers()->at(0)->toString());
	}

	TEST_F(ASTTest, TestTypeDecls)
	{
		int retval = parser.parseFile("test/test_cases/vtTypeDecls.pal");
		ASSERT_EQ(0, retval);

		ParseResult* result = parser.getParseResult();
		ASSERT_NE((ParseResult*)(NULL), result);
		ASSERT_NE((Program*)(NULL), result->program);

		Program* program = result->program;
		ASSERT_NE((Program*)(NULL), program);

		const Declarations* decls = program->getDeclarations();
		ASSERT_NE((Declarations*)(NULL), decls);

		const TypeDeclarationList* types = decls->getTypeDeclarationList();
		ASSERT_NE((TypeDeclarationList*)(NULL), types);
		ASSERT_EQ(4u, types->size());

		TypeDeclaration* decl = types->at(0);
		ASSERT_EQ("newType", decl->getIdentifier()->toString());

		decl = types->at(1);
		ASSERT_EQ("enumType", decl->getIdentifier()->toString());

		decl = types->at(2);
		ASSERT_EQ("arrayType", decl->getIdentifier()->toString());

		decl = types->at(3);
		ASSERT_EQ("recordType", decl->getIdentifier()->toString());
	}

	TEST_F(ASTTest, TestProcDecls)
	{
		int retval = parser.parseFile("test/test_cases/vtProcDecls.pal");
		ASSERT_EQ(0, retval);

		ParseResult* result = parser.getParseResult();
		ASSERT_NE((ParseResult*)(NULL), result);
		ASSERT_NE((Program*)(NULL), result->program);

		Program* program = result->program;
		ASSERT_NE((Program*)(NULL), program);

		const Declarations* decls = program->getDeclarations();
		ASSERT_NE((Declarations*)(NULL), decls);

		const ProcedureDeclarationList* procs = decls->getProcedureDeclarationList();
		ASSERT_NE((ProcedureDeclarationList*)(NULL), procs);
		ASSERT_EQ(2u, procs->size());

		ProcedureDeclaration* decl = procs->at(0);
		ASSERT_NE((ProcedureHeading*)(NULL), decl->getHeading());
		ASSERT_EQ("dostuff", decl->getHeading()->getIdentifier()->toString());
		ASSERT_EQ(NULL, decl->getHeading()->getType());

		ASSERT_EQ(1u, decl->getHeading()->getParameters()->getParameters()->size());
		Parameter* p = decl->getHeading()->getParameters()->getParameters()->at(0);
		ASSERT_EQ("a", p->getName()->toString());
		ASSERT_EQ("integer", p->getType()->toString());

		decl = procs->at(1);
		ASSERT_NE((ProcedureHeading*)(NULL), decl->getHeading());
		ASSERT_EQ("dostuff2", decl->getHeading()->getIdentifier()->toString());

		ASSERT_EQ(2u, decl->getHeading()->getParameters()->getParameters()->size());
		p = decl->getHeading()->getParameters()->getParameters()->at(0);
		ASSERT_EQ("a", p->getName()->toString());
		ASSERT_EQ("integer", p->getType()->toString());

		p = decl->getHeading()->getParameters()->getParameters()->at(1);
		ASSERT_EQ("b", p->getName()->toString());
		ASSERT_EQ("integer", p->getType()->toString());

		ASSERT_EQ("b", p->getName()->toString());
		ASSERT_EQ("integer", p->getType()->toString());

		ASSERT_EQ("string", decl->getHeading()->getType()->toString());
	}

	TEST_F(ASTTest, TestProcWithDecls)
	{
		int retval = parser.parseFile("test/test_cases/vtProcWithDecls.pal");
		ASSERT_EQ(0, retval);

		ParseResult* result = parser.getParseResult();
		ASSERT_NE((ParseResult*)(NULL), result);
		ASSERT_NE((Program*)(NULL), result->program);

		Program* program = result->program;
		ASSERT_NE((Program*)(NULL), program);

		const Declarations* decls = program->getDeclarations();
		ASSERT_NE((Declarations*)(NULL), decls);

		const ProcedureDeclarationList* procs = decls->getProcedureDeclarationList();
		ASSERT_NE((ProcedureDeclarationList*)(NULL), procs);
		ASSERT_EQ(1u, procs->size());

		ProcedureDeclaration* decl = procs->at(0);
		ASSERT_NE((ProcedureHeading*)(NULL), decl->getHeading());
		ASSERT_EQ("dostuff", decl->getHeading()->getIdentifier()->toString());
		ASSERT_EQ(NULL, decl->getHeading()->getType());

		ASSERT_EQ(1u, decl->getHeading()->getParameters()->getParameters()->size());
		Parameter* p = decl->getHeading()->getParameters()->getParameters()->at(0);
		ASSERT_EQ("a", p->getName()->toString());
		ASSERT_EQ("integer", p->getType()->toString());

		// check nested declarations
		ASSERT_EQ(1u, decl->getDeclarations()->getConstantDeclarationList()->size());
		ASSERT_EQ("c", decl->getDeclarations()->getConstantDeclarationList()->at(0)->getIdentifier()->toString());

		ASSERT_EQ(1u, decl->getDeclarations()->getVariableDeclarationList()->size());
		ASSERT_EQ("a", decl->getDeclarations()->getVariableDeclarationList()->at(0)->getIdentifiers()->at(0)->toString());

	}
}

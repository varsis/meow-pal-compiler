#include "gtest/gtest.h"

#include "../src/pal.tab.hpp"
#include "../src/Scanner.hpp"
#include "../src/Parser.hpp"
#include "../src/ErrorManager.hpp"
#include "../src/SymbolTable.hpp"
#include "../src/SemanticHelper.hpp"
#include "../src/AscHelper.hpp"
#include "../src/Error.hpp"
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

	class ParserTest : public ::testing::Test
	{
		protected:

			ParserTest() 
				: dummyOutput("dummyout")
				, semanticHelper(&scanner, &errorManager, &symbolTable)
				, ascHelper(dummyOutput, &symbolTable, &semanticHelper)
				, parser(scanner, errorManager, symbolTable, semanticHelper, ascHelper)
			{
			}

			virtual void SetUp()
			{
				expectedParseResult = Success;
				tokens.clear();
			}

			virtual void TearDown()
			{
				scanner.setTokens(tokens);
				parser.parse();

				int errors = 0;

				ErrorList::iterator it;
				for (it = errorManager.getErrors()->begin();
					it != errorManager.getErrors()->end();
					++it)
				{
					// Only count syntax errors!
					if ((*it)->getErrorCode() < SemanticError)
					{
						++errors;
					}
				}

				bool result = errors > 0;
				
				ASSERT_EQ(expectedParseResult, result)
					<< ">> Incorrect parse result!";

				system("rm dummyout");
			}

			int expectedParseResult;

			MockScanner scanner;
			ErrorManager errorManager;
			SymbolTable symbolTable;
			ofstream dummyOutput;
			SemanticHelper semanticHelper;
			AscHelper ascHelper;
			vector<token_type> tokens;

			PalParser parser;
	};

	TEST_F(ParserTest, TestMinimalProgram)
	{
		tokens.push_back(token::PROGRAM);
		tokens.push_back(token::IDENTIFIER);
		tokens.push_back(token::LEFT_PAREN);
		tokens.push_back(token::IDENTIFIER);
		tokens.push_back(token::COMMA);
		tokens.push_back(token::IDENTIFIER);
		tokens.push_back(token::RIGHT_PAREN);
		tokens.push_back(token::SEMICOLON);

		tokens.push_back(token::PAL_BEGIN);

		tokens.push_back(token::END);
		tokens.push_back(token::PERIOD);
	}

// Procedure definition tests...

	class ProcedureDefTest : public ParserTest
	{
		protected:
			virtual void SetUp()
			{
				ParserTest::SetUp();
				tokens.push_back(token::PROGRAM);
				tokens.push_back(token::IDENTIFIER);
				tokens.push_back(token::LEFT_PAREN);
				tokens.push_back(token::IDENTIFIER);
				tokens.push_back(token::COMMA);
				tokens.push_back(token::IDENTIFIER);
				tokens.push_back(token::RIGHT_PAREN);
				tokens.push_back(token::SEMICOLON);
			}

			virtual void TearDown()
			{
				tokens.push_back(token::PAL_BEGIN);
				tokens.push_back(token::END);
				tokens.push_back(token::PERIOD);
				ParserTest::TearDown();
			}
	};

	TEST_F(ProcedureDefTest, TestProcedureDefMinimal)
	{
		tokens.push_back(token::PROCEDURE);
		tokens.push_back(token::IDENTIFIER);
		tokens.push_back(token::LEFT_PAREN);
		tokens.push_back(token::RIGHT_PAREN);
		tokens.push_back(token::SEMICOLON);

		tokens.push_back(token::PAL_BEGIN);
		tokens.push_back(token::END);
		tokens.push_back(token::SEMICOLON);
	}

	TEST_F(ProcedureDefTest, TestProcedureDef0)
	{
		tokens.push_back(token::PROCEDURE);
		tokens.push_back(token::IDENTIFIER);
		tokens.push_back(token::LEFT_PAREN);
		tokens.push_back(token::RIGHT_PAREN);
		tokens.push_back(token::SEMICOLON);
		
		tokens.push_back(token::CONST);
		tokens.push_back(token::IDENTIFIER);
		tokens.push_back(token::EQ);
		tokens.push_back(token::REAL_CONST);
		tokens.push_back(token::SEMICOLON);

		tokens.push_back(token::PAL_BEGIN);
		tokens.push_back(token::END);
		tokens.push_back(token::SEMICOLON);
	}

	TEST_F(ProcedureDefTest, TestProcedureDef1)
	{
		tokens.push_back(token::PROCEDURE);
		tokens.push_back(token::IDENTIFIER);
		tokens.push_back(token::LEFT_PAREN);
		tokens.push_back(token::RIGHT_PAREN);
		tokens.push_back(token::SEMICOLON);
		
		tokens.push_back(token::CONST);
		tokens.push_back(token::IDENTIFIER);
		tokens.push_back(token::EQ);
		tokens.push_back(token::REAL_CONST);
		tokens.push_back(token::SEMICOLON);

		tokens.push_back(token::VAR);
		tokens.push_back(token::IDENTIFIER);
		tokens.push_back(token::COLON);
		tokens.push_back(token::IDENTIFIER);
		tokens.push_back(token::SEMICOLON);

		tokens.push_back(token::PAL_BEGIN);
		tokens.push_back(token::END);
		tokens.push_back(token::SEMICOLON);
	}

	TEST_F(ProcedureDefTest, TestProcedureDef2)
	{
		tokens.push_back(token::PROCEDURE);
		tokens.push_back(token::IDENTIFIER);
		tokens.push_back(token::LEFT_PAREN);

		tokens.push_back(token::IDENTIFIER);
		tokens.push_back(token::COLON);
		tokens.push_back(token::IDENTIFIER);

		tokens.push_back(token::RIGHT_PAREN);
		tokens.push_back(token::SEMICOLON);
		
		tokens.push_back(token::CONST);
		tokens.push_back(token::IDENTIFIER);
		tokens.push_back(token::EQ);
		tokens.push_back(token::REAL_CONST);
		tokens.push_back(token::SEMICOLON);

		tokens.push_back(token::VAR);
		tokens.push_back(token::IDENTIFIER);
		tokens.push_back(token::COLON);
		tokens.push_back(token::IDENTIFIER);
		tokens.push_back(token::SEMICOLON);

		tokens.push_back(token::PAL_BEGIN);

		tokens.push_back(token::IDENTIFIER);
		tokens.push_back(token::ASSIGN);
		tokens.push_back(token::IDENTIFIER);
		tokens.push_back(token::SEMICOLON);

		tokens.push_back(token::IDENTIFIER);
		tokens.push_back(token::LEFT_PAREN);
		tokens.push_back(token::IDENTIFIER);
		tokens.push_back(token::COMMA);
		tokens.push_back(token::STRING_LITERAL);
		tokens.push_back(token::COMMA);
		tokens.push_back(token::IDENTIFIER);
		tokens.push_back(token::RIGHT_PAREN);
		tokens.push_back(token::SEMICOLON);

		tokens.push_back(token::END);
		tokens.push_back(token::SEMICOLON);
	}

	TEST_F(ProcedureDefTest, TestProcedureDef3)
	{
		expectedParseResult = Failure;

		tokens.push_back(token::PROCEDURE);
		tokens.push_back(token::IDENTIFIER);
		tokens.push_back(token::LEFT_PAREN);

		// this actually isn't legal!
		// p(id, id : type);
		tokens.push_back(token::IDENTIFIER);
		tokens.push_back(token::COMMA);
		tokens.push_back(token::IDENTIFIER);
		tokens.push_back(token::COLON);
		tokens.push_back(token::IDENTIFIER);

		tokens.push_back(token::RIGHT_PAREN);
		tokens.push_back(token::SEMICOLON);

		tokens.push_back(token::PAL_BEGIN);
		tokens.push_back(token::END);
		tokens.push_back(token::SEMICOLON);
	}

	// try function defs...
	TEST_F(ProcedureDefTest, TestFunctionDef0)
	{
		tokens.push_back(token::FUNCTION);
		tokens.push_back(token::IDENTIFIER);
		tokens.push_back(token::LEFT_PAREN);
		tokens.push_back(token::RIGHT_PAREN);
		tokens.push_back(token::COLON);
		tokens.push_back(token::IDENTIFIER);
		tokens.push_back(token::SEMICOLON);

		tokens.push_back(token::PAL_BEGIN);
		tokens.push_back(token::END);
		tokens.push_back(token::SEMICOLON);
	}

	TEST_F(ProcedureDefTest, TestFunctionDef1)
	{
		expectedParseResult = Failure;

		tokens.push_back(token::FUNCTION);
		tokens.push_back(token::IDENTIFIER);
		tokens.push_back(token::LEFT_PAREN);

		// this actually isn't legal!
		// fn(id, id : type) : type;
		tokens.push_back(token::IDENTIFIER);
		tokens.push_back(token::COMMA);
		tokens.push_back(token::IDENTIFIER);
		tokens.push_back(token::COLON);
		tokens.push_back(token::IDENTIFIER);

		tokens.push_back(token::RIGHT_PAREN);
		tokens.push_back(token::COLON);
		tokens.push_back(token::IDENTIFIER);
		tokens.push_back(token::SEMICOLON);

		tokens.push_back(token::PAL_BEGIN);
		tokens.push_back(token::END);
		tokens.push_back(token::SEMICOLON);
	}

// Variable declaration tests...

	class VarDeclarationTest : public ParserTest
	{
		protected:
			virtual void SetUp()
			{
				ParserTest::SetUp();
				tokens.push_back(token::PROGRAM);
				tokens.push_back(token::IDENTIFIER);
				tokens.push_back(token::LEFT_PAREN);
				tokens.push_back(token::IDENTIFIER);
				tokens.push_back(token::COMMA);
				tokens.push_back(token::IDENTIFIER);
				tokens.push_back(token::RIGHT_PAREN);
				tokens.push_back(token::SEMICOLON);
			}

			virtual void TearDown()
			{
				tokens.push_back(token::PAL_BEGIN);
				tokens.push_back(token::END);
				tokens.push_back(token::PERIOD);
				ParserTest::TearDown();
			}
	};

	TEST_F(VarDeclarationTest, ArrayVarDeclarationTest)
	{
		// var
		//		fibList : array[0..50] of integer;
		tokens.push_back(token::VAR);

		tokens.push_back(token::IDENTIFIER);
		tokens.push_back(token::COLON);
		tokens.push_back(token::ARRAY);
		tokens.push_back(token::LEFT_BRACKET);
		tokens.push_back(token::INT_CONST);
		tokens.push_back(token::UPTO);
		tokens.push_back(token::INT_CONST);
		tokens.push_back(token::RIGHT_BRACKET);
		tokens.push_back(token::OF);
		tokens.push_back(token::IDENTIFIER);
		tokens.push_back(token::SEMICOLON);
	}

// Array declaration tests...

	class ArrayTypeDeclarationTest : public ParserTest
	{
		protected:
			virtual void SetUp()
			{
				ParserTest::SetUp();

				tokens.push_back(token::PROGRAM);
				tokens.push_back(token::IDENTIFIER);
				tokens.push_back(token::LEFT_PAREN);
				tokens.push_back(token::IDENTIFIER);
				tokens.push_back(token::COMMA);
				tokens.push_back(token::IDENTIFIER);
				tokens.push_back(token::RIGHT_PAREN);
				tokens.push_back(token::SEMICOLON);

				tokens.push_back(token::TYPE);
				tokens.push_back(token::IDENTIFIER);
				tokens.push_back(token::EQ);
				tokens.push_back(token::ARRAY);
			}

			virtual void TearDown()
			{
				tokens.push_back(token::OF);
				tokens.push_back(token::IDENTIFIER);
				tokens.push_back(token::SEMICOLON);
				tokens.push_back(token::PAL_BEGIN);
				tokens.push_back(token::END);
				tokens.push_back(token::PERIOD);

				ParserTest::TearDown();
			}
	};

	TEST_F(ArrayTypeDeclarationTest, TestArrayDeclarations0)
	{
		tokens.push_back(token::LEFT_BRACKET);
		tokens.push_back(token::INT_CONST);
		tokens.push_back(token::UPTO);
		tokens.push_back(token::INT_CONST);
		tokens.push_back(token::RIGHT_BRACKET);
	} // type array[1..10] of bool;

	TEST_F(ArrayTypeDeclarationTest, TestArrayDeclarations1)
	{
		tokens.push_back(token::LEFT_BRACKET);

		tokens.push_back(token::LEFT_PAREN);
		tokens.push_back(token::IDENTIFIER);
		tokens.push_back(token::RIGHT_PAREN);

		tokens.push_back(token::UPTO);

		tokens.push_back(token::LEFT_PAREN);
		tokens.push_back(token::IDENTIFIER);
		tokens.push_back(token::RIGHT_PAREN);

		tokens.push_back(token::RIGHT_BRACKET);
	} // type array[(id) .. (id)] of bool;

	// With the supplied grammar, these are 'legal' but PAL doesn't allow 
	// anonymous enumerations in array types, so the next two SHOULD fail to parse

	TEST_F(ArrayTypeDeclarationTest, TestArrayDeclarations2)
	{
		expectedParseResult = Failure;

		tokens.push_back(token::LEFT_BRACKET);
		tokens.push_back(token::LEFT_PAREN);
		tokens.push_back(token::IDENTIFIER);
		tokens.push_back(token::RIGHT_PAREN);
		tokens.push_back(token::RIGHT_BRACKET);
	} // type array[(id)]

	TEST_F(ArrayTypeDeclarationTest, TestArrayDeclarations3)
	{
		expectedParseResult = Failure;

		tokens.push_back(token::LEFT_BRACKET);
		tokens.push_back(token::LEFT_PAREN);
		tokens.push_back(token::IDENTIFIER);
		tokens.push_back(token::COMMA);
		tokens.push_back(token::IDENTIFIER);
		tokens.push_back(token::RIGHT_PAREN);
		tokens.push_back(token::RIGHT_BRACKET);
	} // type array[(id, id)] of bool;

// Type declaration tests...

	class TypeDeclarationTest : public ParserTest
	{
		protected:
			virtual void SetUp()
			{
				ParserTest::SetUp();

				tokens.push_back(token::PROGRAM);
				tokens.push_back(token::IDENTIFIER);
				tokens.push_back(token::LEFT_PAREN);
				tokens.push_back(token::IDENTIFIER);
				tokens.push_back(token::COMMA);
				tokens.push_back(token::IDENTIFIER);
				tokens.push_back(token::RIGHT_PAREN);
				tokens.push_back(token::SEMICOLON);

				tokens.push_back(token::TYPE);
			}

			virtual void TearDown()
			{
				tokens.push_back(token::PAL_BEGIN);
				tokens.push_back(token::END);
				tokens.push_back(token::PERIOD);

				ParserTest::TearDown();
			}
	};

	TEST_F(TypeDeclarationTest, EnumeratedTypeDef1)
	{
		// enumerated type
		tokens.push_back(token::IDENTIFIER);
		tokens.push_back(token::EQ);
		tokens.push_back(token::LEFT_PAREN);
		tokens.push_back(token::IDENTIFIER);
		tokens.push_back(token::COMMA);
		tokens.push_back(token::IDENTIFIER);
		tokens.push_back(token::COMMA);
		tokens.push_back(token::IDENTIFIER);
		tokens.push_back(token::RIGHT_PAREN);
		tokens.push_back(token::SEMICOLON);
	}

	TEST_F(TypeDeclarationTest, EnumeratedTypeDef2)
	{
		// type T = (1,2,3);
		expectedParseResult = Failure;
		tokens.push_back(token::IDENTIFIER);
		tokens.push_back(token::EQ);
		tokens.push_back(token::LEFT_PAREN);
		tokens.push_back(token::INT_CONST);
		tokens.push_back(token::COMMA);
		tokens.push_back(token::INT_CONST);
		tokens.push_back(token::COMMA);
		tokens.push_back(token::INT_CONST);
		tokens.push_back(token::RIGHT_PAREN);
		tokens.push_back(token::SEMICOLON);
	}

	TEST_F(TypeDeclarationTest, ArrayDef1)
	{
		tokens.push_back(token::IDENTIFIER);
		tokens.push_back(token::EQ);
		tokens.push_back(token::ARRAY);

		tokens.push_back(token::LEFT_BRACKET);
		tokens.push_back(token::INT_CONST);
		tokens.push_back(token::UPTO);
		tokens.push_back(token::INT_CONST);
		tokens.push_back(token::RIGHT_BRACKET);

		tokens.push_back(token::OF);
		tokens.push_back(token::IDENTIFIER);
		tokens.push_back(token::SEMICOLON);
	}

	TEST_F(TypeDeclarationTest, 2DArrayDef1)
	{
		// T = array[1..10,1..10] of integer;
		// TODO: determine if multidimensional arrays are legal in PAL
		expectedParseResult = Failure;

		tokens.push_back(token::IDENTIFIER);
		tokens.push_back(token::EQ);
		tokens.push_back(token::ARRAY);

		tokens.push_back(token::LEFT_BRACKET);
		tokens.push_back(token::INT_CONST);
		tokens.push_back(token::UPTO);
		tokens.push_back(token::INT_CONST);
		tokens.push_back(token::COMMA);
		tokens.push_back(token::INT_CONST);
		tokens.push_back(token::UPTO);
		tokens.push_back(token::INT_CONST);
		tokens.push_back(token::RIGHT_BRACKET);

		tokens.push_back(token::OF);
		tokens.push_back(token::IDENTIFIER);
		tokens.push_back(token::SEMICOLON);
	}

	TEST_F(TypeDeclarationTest, RecordDef1)
	{
		// T = record 
		//		age : integer;
		//		end;
		tokens.push_back(token::IDENTIFIER);
		tokens.push_back(token::EQ);
		tokens.push_back(token::RECORD);

		tokens.push_back(token::IDENTIFIER);
		tokens.push_back(token::COLON);
		tokens.push_back(token::IDENTIFIER);

		tokens.push_back(token::END);
		tokens.push_back(token::SEMICOLON);
	}

// Statement tests...

	class StatementsTest : public ParserTest
	{
		protected:
			virtual void SetUp()
			{
				ParserTest::SetUp();

				tokens.push_back(token::PROGRAM);
				tokens.push_back(token::IDENTIFIER);
				tokens.push_back(token::LEFT_PAREN);
				tokens.push_back(token::IDENTIFIER);
				tokens.push_back(token::COMMA);
				tokens.push_back(token::IDENTIFIER);
				tokens.push_back(token::RIGHT_PAREN);
				tokens.push_back(token::SEMICOLON);
				tokens.push_back(token::PAL_BEGIN);
			}

			virtual void TearDown()
			{
				tokens.push_back(token::END);
				tokens.push_back(token::PERIOD);

				ParserTest::TearDown();
			}
	};

	TEST_F(StatementsTest, IdAssign1)
	{
		// id assign
		tokens.push_back(token::IDENTIFIER);
		tokens.push_back(token::ASSIGN);
		tokens.push_back(token::INT_CONST);
		tokens.push_back(token::SEMICOLON);
	}

	TEST_F(StatementsTest, ArrayAssign1)
	{
		// array assign
		tokens.push_back(token::IDENTIFIER);
		tokens.push_back(token::LEFT_BRACKET);
		tokens.push_back(token::INT_CONST);
		tokens.push_back(token::RIGHT_BRACKET);
		tokens.push_back(token::ASSIGN);
		tokens.push_back(token::INT_CONST);
		tokens.push_back(token::SEMICOLON);
	}

	TEST_F(StatementsTest, FunctionCall1)
	{
		// function call
		tokens.push_back(token::IDENTIFIER);
		tokens.push_back(token::LEFT_PAREN);
		tokens.push_back(token::IDENTIFIER);
		tokens.push_back(token::LEFT_BRACKET);
		tokens.push_back(token::IDENTIFIER);
		tokens.push_back(token::RIGHT_BRACKET);
		tokens.push_back(token::RIGHT_PAREN);
		tokens.push_back(token::SEMICOLON);
	}

	TEST_F(StatementsTest, WhileTest1)
	{
		// while loop
		tokens.push_back(token::WHILE);
		tokens.push_back(token::LEFT_PAREN);
		tokens.push_back(token::IDENTIFIER);
		tokens.push_back(token::LT);
		tokens.push_back(token::INT_CONST);
		tokens.push_back(token::RIGHT_PAREN);
		tokens.push_back(token::DO);
		tokens.push_back(token::PAL_BEGIN);

			tokens.push_back(token::IDENTIFIER);
			tokens.push_back(token::ASSIGN);
			tokens.push_back(token::IDENTIFIER);
			tokens.push_back(token::PLUS);
			tokens.push_back(token::INT_CONST);
			tokens.push_back(token::SEMICOLON);

		tokens.push_back(token::END);
		tokens.push_back(token::SEMICOLON);
	}

	TEST_F(StatementsTest, IfTest1)
	{
        // if a = 0 then
        // begin
           // a := 1;
        // end        
		tokens.push_back(token::IF);
		tokens.push_back(token::IDENTIFIER);
		tokens.push_back(token::EQ);
		tokens.push_back(token::INT_CONST);
		tokens.push_back(token::THEN);
		tokens.push_back(token::PAL_BEGIN);
			tokens.push_back(token::IDENTIFIER);
			tokens.push_back(token::ASSIGN);
			tokens.push_back(token::INT_CONST);
			tokens.push_back(token::SEMICOLON);
		tokens.push_back(token::END);
	}

	TEST_F(StatementsTest, IfTest2)
	{
        // if a = 0 then
        // begin
           // a := 1
        // end        
		tokens.push_back(token::IF);
		tokens.push_back(token::IDENTIFIER);
		tokens.push_back(token::EQ);
		tokens.push_back(token::INT_CONST);
		tokens.push_back(token::THEN);
		tokens.push_back(token::PAL_BEGIN);
			tokens.push_back(token::IDENTIFIER);
			tokens.push_back(token::ASSIGN);
			tokens.push_back(token::INT_CONST);
			// TODO No semicolon! is this ok??
		tokens.push_back(token::END);
	}

	/*
	TEST_F(StatementsTest, EmptyIfTest)
	{
        // if (true) then;
		tokens.push_back(token::IF);
		tokens.push_back(token::LEFT_PAREN);
		tokens.push_back(token::IDENTIFIER);
		tokens.push_back(token::RIGHT_PAREN);
		tokens.push_back(token::THEN);
		tokens.push_back(token::SEMICOLON);
	}

	TEST_F(StatementsTest, EmptyIfElseTest)
	{
        // if (true) then else;
        // -- this compiles without error/warning in fpc!
        // TODO - can 'matched_stat' be empty?
		tokens.push_back(token::IF);
		tokens.push_back(token::LEFT_PAREN);
		tokens.push_back(token::IDENTIFIER);
		tokens.push_back(token::RIGHT_PAREN);
		tokens.push_back(token::THEN);
		tokens.push_back(token::ELSE);
		tokens.push_back(token::SEMICOLON);
	}
	*/


	TEST_F(StatementsTest, IfElseTest1)
	{
        // if a = 0 then
        // begin
           // a := 1;
        // end        
        // else
        // begin
           // a := 2;
        // end        
		tokens.push_back(token::IF);
		tokens.push_back(token::IDENTIFIER);
		tokens.push_back(token::EQ);
		tokens.push_back(token::INT_CONST);
		tokens.push_back(token::THEN);
		tokens.push_back(token::PAL_BEGIN);
			tokens.push_back(token::IDENTIFIER);
			tokens.push_back(token::ASSIGN);
			tokens.push_back(token::INT_CONST);
			tokens.push_back(token::SEMICOLON);
		tokens.push_back(token::END);
		tokens.push_back(token::ELSE);
		tokens.push_back(token::PAL_BEGIN);
			tokens.push_back(token::IDENTIFIER);
			tokens.push_back(token::ASSIGN);
			tokens.push_back(token::IDENTIFIER);
			tokens.push_back(token::SEMICOLON);
		tokens.push_back(token::END);
	}

	TEST_F(StatementsTest, ProcInvokeTest1)
	{
		// foo();
		tokens.push_back(token::IDENTIFIER);
		tokens.push_back(token::LEFT_PAREN);
		tokens.push_back(token::RIGHT_PAREN);
	}

	TEST_F(StatementsTest, ProcInvokeTest2)
	{
		// foo(a, b);
		tokens.push_back(token::IDENTIFIER);
		tokens.push_back(token::LEFT_PAREN);
		tokens.push_back(token::IDENTIFIER);
		tokens.push_back(token::COMMA);
		tokens.push_back(token::IDENTIFIER);
		tokens.push_back(token::RIGHT_PAREN);
	}
}

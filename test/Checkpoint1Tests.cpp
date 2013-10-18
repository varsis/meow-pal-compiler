#include <fstream>
#include "gtest/gtest.h"

#include "../src/Error.hpp"
#include "../src/ErrorManager.hpp"
#include "../src/Parser.hpp"
#include "../src/pal.tab.h"

using namespace std;
namespace Meow
{
	typedef PalParser::token token;
	typedef PalParser::token_type token_type;

#define PARSE_FILE(filename, expected) \
	int retval = parser->parseFile(filename); \
	EXPECT_EQ(retval, expected);

#define GET_ERRORS(expected) \
	const ErrorList* errors = errorManager->getErrors(); \
	EXPECT_EQ(expected, errors->size()); \
	multiset<Error*>::iterator errIt = errors->begin();

#define EXPECT_ERROR(errorcode, linenumber) \
	ASSERT_NE(errIt, errors->end());\
	EXPECT_EQ(errorcode, (*errIt)->getErrorCode());\
	EXPECT_EQ(linenumber, (*errIt)->getLineNumber());\
	++errIt

	enum ParseRetval
	{
		Success = 0,
		Failure = 1
	};

	class Checkpoint1Tests : public ::testing::Test
	{
		protected:

			Checkpoint1Tests() 
			{
			}

			virtual void SetUp()
			{
				errorManager = new ErrorManager();
				parser = new Parser(errorManager);
			}

			virtual void TearDown()
			{
				delete errorManager;
				delete parser;
			}

			ErrorManager *errorManager;
			Parser *parser;
	};

	TEST_F(Checkpoint1Tests, Test_0)
	{
		PARSE_FILE("test/test_cases/checkpoint_1/0.pal", Failure);
		GET_ERRORS(3u);
		EXPECT_ERROR(InvalidIdentifier, 11);
		EXPECT_ERROR(InvalidIdentifier, 20);
		// TODO
		//EXPECT_ERROR(InvalidNumber, 21);
	}

	TEST_F(Checkpoint1Tests, Test_1)
	{
		PARSE_FILE("test/test_cases/checkpoint_1/1.pal", Failure);
		GET_ERRORS(3u);
		EXPECT_ERROR(InvalidIdentifier, 12);
		EXPECT_ERROR(InvalidIdentifier, 13);
		// TODO
		//EXPECT_ERROR(InvalidStringCharacter, 14);
	}

	TEST_F(Checkpoint1Tests, Test_2)
	{
		PARSE_FILE("test/test_cases/checkpoint_1/2.pal", Failure);
		GET_ERRORS(1u);
		// TODO number issue
		EXPECT_ERROR(UnrecognizedSymbol, 9);
	}

	// TODO array : array[1E1 .. 2]; (syntax)

	TEST_F(Checkpoint1Tests, Test_3)
	{
		PARSE_FILE("test/test_cases/checkpoint_1/3.pal", Failure);
		GET_ERRORS(3u);
		EXPECT_ERROR(UnrecognizedSymbol, 12);
		EXPECT_ERROR(UnrecognizedSymbol, 13);
		EXPECT_ERROR(UnrecognizedSymbol, 14);
	}

	TEST_F(Checkpoint1Tests, Test_4)
	{
		PARSE_FILE("test/test_cases/checkpoint_1/4.pal", Failure);
		GET_ERRORS(3u);
		EXPECT_ERROR(UnrecognizedSymbol, 13);
	}

	TEST_F(Checkpoint1Tests, Test_5)
	{
		PARSE_FILE("test/test_cases/checkpoint_1/5.pal", Failure);
		GET_ERRORS(1u);
		EXPECT_ERROR(InvalidExpression, 12);

		// FIXME -- getting like 5 errors here!
	}

	TEST_F(Checkpoint1Tests, Test_6)
	{
		PARSE_FILE("test/test_cases/checkpoint_1/6.pal", Failure);
		GET_ERRORS(4u);
		EXPECT_ERROR(SyntaxError, 5);
		EXPECT_ERROR(InvalidProgramHeader, 5);
		EXPECT_ERROR(InvalidProcDecl, 19);
		EXPECT_ERROR(SyntaxError, 32);
	}

	TEST_F(Checkpoint1Tests, Test_7)
	{
		PARSE_FILE("test/test_cases/checkpoint_1/7.pal", Failure);
		GET_ERRORS(3u);
		EXPECT_ERROR(SyntaxError, 19);
		EXPECT_ERROR(InvalidExpression, 19);
		EXPECT_ERROR(SyntaxError, 21);
	}
}

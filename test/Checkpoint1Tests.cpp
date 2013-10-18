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
		int retval = parser->parseFile("test/test_cases/checkpoint_1/0.pal");

		const multiset<Error*,classcomp>* errors = errorManager->getErrors();
		
		// Should fail to parse
		EXPECT_EQ(1, retval);

		// Should have 3 errors
		EXPECT_EQ(3u, errors->size()); 

		multiset<Error*>::iterator errIt = errors->begin();
		Error* error;

		ASSERT_NE(errIt, errors->end());

		error = *errIt;

		EXPECT_EQ(InvalidIdentifier, error->getErrorCode());
		EXPECT_EQ(11u, error->getLineNumber());

		ASSERT_NE(errIt, errors->end());
		error = *(errIt++);

		EXPECT_EQ(InvalidIdentifier, error->getErrorCode());
		EXPECT_EQ(20u, error->getLineNumber());

		ASSERT_NE(errIt, errors->end());
		error = *(errIt++);

		// TODO InvalidNumber
		EXPECT_EQ(SyntaxError, error->getErrorCode());
		EXPECT_EQ(21u, error->getLineNumber());
	}
}

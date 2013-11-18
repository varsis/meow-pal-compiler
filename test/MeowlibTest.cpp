#include <fstream>
#include <stdio.h>

#include "gtest/gtest.h"

using namespace std;

namespace Meow
{
	TEST(MeowlibTest, TestOdd)
	{
		ifstream ascsource("asc/meowlib/odd.asc");
		ofstream testfile("test/asc/test.asc");

		testfile << "\tCONSTI 0" << endl;
		testfile << "\tCALL 0, meowlib_odd" << endl;
		testfile << "\tWRITEI" << endl;
		// expect 0

		testfile << "\tCONSTI 1" << endl;
		testfile << "\tCALL 0, meowlib_odd" << endl;
		testfile << "\tWRITEI" << endl;
		// expect 1

		testfile << "\tCONSTI 14" << endl;
		testfile << "\tCALL 0, meowlib_odd" << endl;
		testfile << "\tWRITEI" << endl;
		// expect 0

		testfile << "\tCONSTI 255" << endl;
		testfile << "\tCALL 0, meowlib_odd" << endl;
		testfile << "\tWRITEI" << endl;
		// expect 1

		testfile << "\tCONSTI 1034" << endl;
		testfile << "\tCALL 0, meowlib_odd" << endl;
		testfile << "\tWRITEI" << endl;
		// expect 0

		testfile << "\tCONSTI 50243" << endl;
		testfile << "\tCALL 0, meowlib_odd" << endl;
		testfile << "\tWRITEI" << endl;
		// expect 1

		testfile << "\tSTOP" << endl;

		// append builtin function implmentation
		testfile << ascsource.rdbuf();

		testfile.close();
		ascsource.close();

		FILE* ascout = popen("cat test/asc/test.asc | bin/asc", "r");
		ASSERT_NE(ascout, (void*)0);

		int retval;

		ASSERT_EQ(fscanf(ascout, "%d", &retval), 1);
		EXPECT_EQ(retval, 0);

		ASSERT_EQ(fscanf(ascout, "%d", &retval), 1);
		EXPECT_EQ(retval, 1);

		ASSERT_EQ(fscanf(ascout, "%d", &retval), 1);
		EXPECT_EQ(retval, 0);

		ASSERT_EQ(fscanf(ascout, "%d", &retval), 1);
		EXPECT_EQ(retval, 1);

		ASSERT_EQ(fscanf(ascout, "%d", &retval), 1);
		EXPECT_EQ(retval, 0);

		ASSERT_EQ(fscanf(ascout, "%d", &retval), 1);
		EXPECT_EQ(retval, 1);

		pclose(ascout);
	}
}

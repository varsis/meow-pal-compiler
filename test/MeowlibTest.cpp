#include <fstream>
#include <stdio.h>

#include "gtest/gtest.h"

using namespace std;

namespace Meow
{
	TEST(MeowlibTest, TestOdd)
	{
		ifstream odd_source("asc/meowlib/odd.asc");
		ifstream abs_source("asc/meowlib/abs.asc");
		ofstream testfile("test/asc/test.asc");

		testfile << "\tCONSTI 0" << endl;
		testfile << "\tCALL 0, ml_odd" << endl;
		testfile << "\tWRITEI" << endl;
		// expect 0

		testfile << "\tCONSTI 1" << endl;
		testfile << "\tCALL 0, ml_odd" << endl;
		testfile << "\tWRITEI" << endl;
		// expect 1

		testfile << "\tCONSTI 14" << endl;
		testfile << "\tCALL 0, ml_odd" << endl;
		testfile << "\tWRITEI" << endl;
		// expect 0

		testfile << "\tCONSTI 255" << endl;
		testfile << "\tCALL 0, ml_odd" << endl;
		testfile << "\tWRITEI" << endl;
		// expect 1

		testfile << "\tCONSTI 1034" << endl;
		testfile << "\tCALL 0, ml_odd" << endl;
		testfile << "\tWRITEI" << endl;
		// expect 0

		testfile << "\tCONSTI 50243" << endl;
		testfile << "\tCALL 0, ml_odd" << endl;
		testfile << "\tWRITEI" << endl;
		// expect 1

		testfile << "\tSTOP" << endl;

		// append builtin function implmentation
		testfile << abs_source.rdbuf();	
		testfile << odd_source.rdbuf();

		testfile.close();
		abs_source.close();
		odd_source.close();

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

	TEST(MeowlibTest, TestWriteInteger)
	{
		ifstream ascsource("asc/meowlib/write_integer.asc");
		ofstream testfile("test/asc/test.asc");

		testfile << "\tCONSTI 0" << endl;
		testfile << "\tCALL 0, ml_write_integer" << endl;

		testfile << "\tCONSTI 10" << endl;
		testfile << "\tWRITEC" << endl;

		testfile << "\tCONSTI 1" << endl;
		testfile << "\tCALL 0, ml_write_integer" << endl;

		testfile << "\tCONSTI 10" << endl;
		testfile << "\tWRITEC" << endl;

		testfile << "\tCONSTI -14" << endl;
		testfile << "\tCALL 0, ml_write_integer" << endl;

		testfile << "\tCONSTI 10" << endl;
		testfile << "\tWRITEC" << endl;

		testfile << "\tCONSTI 255" << endl;
		testfile << "\tCALL 0, ml_write_integer" << endl;

		testfile << "\tCONSTI 10" << endl;
		testfile << "\tWRITEC" << endl;

		testfile << "\tCONSTI -1034" << endl;
		testfile << "\tCALL 0, ml_write_integer" << endl;

		testfile << "\tCONSTI 10" << endl;
		testfile << "\tWRITEC" << endl;

		testfile << "\tCONSTI 50243" << endl;
		testfile << "\tCALL 0, ml_write_integer" << endl;

		testfile << "\tCONSTI 10" << endl;
		testfile << "\tWRITEC" << endl;

		testfile << "\tSTOP" << endl;

		// append builtin function implmentation
		testfile << ascsource.rdbuf();

		testfile.close();
		ascsource.close();

		FILE* ascout = popen("cat test/asc/test.asc | bin/asc", "r");
		ASSERT_NE(ascout, (void*)0);

		int value;

		ASSERT_EQ(fscanf(ascout, "%d", &value), 1);
		EXPECT_EQ(value, 0);

		ASSERT_EQ(fscanf(ascout, "%d", &value), 1);
		EXPECT_EQ(value, 1);

		ASSERT_EQ(fscanf(ascout, "%d", &value), 1);
		EXPECT_EQ(value, -14);

		ASSERT_EQ(fscanf(ascout, "%d", &value), 1);
		EXPECT_EQ(value, 255);

		ASSERT_EQ(fscanf(ascout, "%d", &value), 1);
		EXPECT_EQ(value, -1034);

		ASSERT_EQ(fscanf(ascout, "%d", &value), 1);
		EXPECT_EQ(value, 50243);

		pclose(ascout);
	}

	TEST(MeowlibTest, TestWriteString)
	{
		ifstream ascsource("asc/meowlib/write_string.asc");
		ofstream testfile("test/asc/test.asc");

		testfile << "\tCONSTI 104" << endl; // h
		testfile << "\tCONSTI 101" << endl; // e
		testfile << "\tCONSTI 108" << endl; // l
		testfile << "\tCONSTI 108" << endl; // l
		testfile << "\tCONSTI 111" << endl; // o
		testfile << "\tCONSTI 0" << endl; // 0
		testfile << "\tCALL 0, ml_write_string" << endl;
		testfile << "\tADJUST -6" << endl; // 0

		testfile << "\tCONSTI 10" << endl;
		testfile << "\tWRITEC" << endl;

		testfile << "\tCONSTI 110" << endl; // n
		testfile << "\tCONSTI 111" << endl; // o
		testfile << "\tCONSTI 111" << endl; // o
		testfile << "\tCONSTI 111" << endl; // o
		testfile << "\tCONSTI 0" << endl; // 0
		testfile << "\tCALL 0, ml_write_string" << endl;
		testfile << "\tADJUST -5" << endl; // 0

		testfile << "\tCONSTI 10" << endl;
		testfile << "\tWRITEC" << endl;

		testfile << "\tCONSTI 104" << endl; // h
		testfile << "\tCONSTI 101" << endl; // e
		testfile << "\tCONSTI 108" << endl; // l
		testfile << "\tCONSTI 108" << endl; // l
		testfile << "\tCONSTI 111" << endl; // o
		testfile << "\tCONSTI 0" << endl; // 0
		testfile << "\tCALL 0, ml_write_string" << endl;
		testfile << "\tADJUST -6" << endl; // 0

		testfile << "\tCONSTI 10" << endl;
		testfile << "\tWRITEC" << endl;
		testfile << "\tSTOP" << endl;

		// append builtin function implmentation
		testfile << ascsource.rdbuf();

		testfile.close();
		ascsource.close();

		FILE* ascout = popen("cat test/asc/test.asc | bin/asc", "r");
		ASSERT_NE(ascout, (void*)0);

		char buf[256];

		ASSERT_EQ(fscanf(ascout, "%s", buf), 1);
		EXPECT_EQ(string(buf), "hello");

		ASSERT_EQ(fscanf(ascout, "%s", buf), 1);
		EXPECT_EQ(string(buf), "nooo");

		ASSERT_EQ(fscanf(ascout, "%s", buf), 1);
		EXPECT_EQ(string(buf), "hello");

		pclose(ascout);
	}
}

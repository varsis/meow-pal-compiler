#include <fstream>
#include <stdio.h>

#include "gtest/gtest.h"

using namespace std;

namespace Meow
{
	TEST(CodegenTest, TestWriteInt)
	{
		ofstream testfile("test/asc/test.pal");

		testfile << "program test(input, output);" << endl;
		testfile << "begin" << endl;
		testfile << "   writeln(1);" << endl;
		testfile << "end." << endl;

		testfile.close();

		FILE* palout = popen("bin/pal -n test/asc/test.pal", "r");
		ASSERT_NE(palout, (void*)0);

		int i;

		ASSERT_EQ(fscanf(palout, "%d", &i), 1);
		EXPECT_EQ(i, 1);

		pclose(palout);
	}

	TEST(CodegenTest, TestWriteReal)
	{
		ofstream testfile("test/asc/test.pal");

		testfile << "program test(input, output);" << endl;
		testfile << "begin" << endl;
		testfile << "   writeln(3.14);" << endl;
		testfile << "end." << endl;

		testfile.close();

		FILE* palout = popen("bin/pal -n test/asc/test.pal", "r");
		ASSERT_NE(palout, (void*)0);

		float i;

		ASSERT_EQ(fscanf(palout, "%f", &i), 1);
		EXPECT_EQ(i, 3.14);

		pclose(palout);
	}

	TEST(CodegenTest, TestWriteChar)
	{
		ofstream testfile("test/asc/test.pal");

		testfile << "program test(input, output);" << endl;
		testfile << "begin" << endl;
		testfile << "   writeln('z');" << endl;
		testfile << "end." << endl;

		testfile.close();

		FILE* palout = popen("bin/pal -n test/asc/test.pal", "r");
		ASSERT_NE(palout, (void*)0);

		char buf[256];

		ASSERT_EQ(fscanf(palout, "%s", buf), 1);
		EXPECT_EQ(string(buf), "z");

		pclose(palout);
	}

	TEST(CodegenTest, TestWriteString)
	{
		ofstream testfile("test/asc/test.pal");

		testfile << "program test(input, output);" << endl;
		testfile << "begin" << endl;
		testfile << "   writeln('hello world');" << endl;
		testfile << "end." << endl;

		testfile.close();

		FILE* palout = popen("bin/pal -n test/asc/test.pal", "r");
		ASSERT_NE(palout, (void*)0);

		char buf[256];

		ASSERT_EQ(fscanf(palout, "%s", buf), 1);
		EXPECT_EQ(string(buf), "hello world");

		pclose(palout);
	}
}

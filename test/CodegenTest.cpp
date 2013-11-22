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
	
	TEST(CodegenTest, TestAdditionInt)
	{
		ofstream testfile("test/asc/test.pal");
		
		testfile << "program test(input, output);" << endl;
		testfile << "begin" << endl;
		// print 12
		testfile << "   writeln(10 + 2);" << endl;
		testfile << "end." << endl;
		
		testfile.close();
		
		FILE* palout = popen("bin/pal -n test/asc/test.pal", "r");
		ASSERT_NE(palout, (void*)0);
		
		int i;
		
		ASSERT_EQ(fscanf(palout, "%d", &i), 1);
		EXPECT_EQ(i, 12);
		
		pclose(palout);
	}
	
	TEST(CodegenTest, TestAdditionReal)
	{
		ofstream testfile("test/asc/testAddReal.pal");
		
		testfile << "program test(input, output);" << endl;
		testfile << "begin" << endl;
		// print 12.2
		testfile << "   writeln(10.2 + 2.0);" << endl;
		testfile << "end." << endl;
		
		testfile.close();
		
		FILE* palout = popen("bin/pal -S -n test/asc/testAddReal.pal", "r");
		
		ASSERT_NE(palout, (void*)0);
		
		float i;
		
		ASSERT_EQ(fscanf(palout, "%f", &i), 1);
		EXPECT_FLOAT_EQ(i, 12.2);
		
		pclose(palout);
	}
	
	TEST(CodegenTest, TestAdditionRealInt)
	{
		ofstream testfile("test/asc/testRealIntAdd.pal");
		
		testfile << "program test(input, output);" << endl;
		testfile << "begin" << endl;
		// print 12.2
		testfile << "   writeln(10.2 + 2);" << endl;
		testfile << "end." << endl;
		
		testfile.close();
		
		FILE* palout = popen("bin/pal -n test/asc/testRealIntAdd.pal", "r");
		ASSERT_NE(palout, (void*)0);
		
		float i;
		
		ASSERT_EQ(fscanf(palout, "%f", &i), 1);
		EXPECT_FLOAT_EQ(i, 12.2);
		
		pclose(palout);
	}
	
	TEST(CodegenTest, TestAdditionIntReal)
	{
		ofstream testfile("test/asc/testIntRealAdd.pal");
		
		testfile << "program test(input, output);" << endl;
		testfile << "begin" << endl;
		// print 12.2
		testfile << "   writeln(10 + 2.2);" << endl;
		testfile << "end." << endl;
		
		testfile.close();
		
		FILE* palout = popen("bin/pal -n test/asc/testIntRealAdd.pal", "r");
		ASSERT_NE(palout, (void*)0);
		
		float i;
		
		ASSERT_EQ(fscanf(palout, "%f", &i), 1);
		EXPECT_FLOAT_EQ(i, 12.2);
		
		pclose(palout);
	}
	
	TEST(CodegenTest, TestMultiplyReal)
	{
		ofstream testfile("test/asc/test.pal");
		
		testfile << "program test(input, output);" << endl;
		testfile << "begin" << endl;
		// print 12.2
		testfile << "   writeln(10.0 * 2.5);" << endl;
		testfile << "end." << endl;
		
		testfile.close();
		
		FILE* palout = popen("bin/pal -n test/asc/test.pal", "r");
		ASSERT_NE(palout, (void*)0);
		
		float i;
		
		ASSERT_EQ(fscanf(palout, "%f", &i), 1);
		EXPECT_FLOAT_EQ(i, 25.0);
		
		
		pclose(palout);
	}
	
	
	TEST(CodegenTest, TestMultiplyIntReal)
	{
		ofstream testfile("test/asc/test.pal");
		
		testfile << "program test(input, output);" << endl;
		testfile << "begin" << endl;
		// print 12.2
		testfile << "   writeln(10 * 2.5);" << endl;
		testfile << "end." << endl;
		
		testfile.close();
		
		FILE* palout = popen("bin/pal -n test/asc/test.pal", "r");
		ASSERT_NE(palout, (void*)0);
		
		float i;
		
		ASSERT_EQ(fscanf(palout, "%f", &i), 1);
		EXPECT_FLOAT_EQ(i, 25.0);
		
		pclose(palout);
	}
	
	TEST(CodegenTest, TestMultiplyRealInt)
	{
		ofstream testfile("test/asc/test.pal");
		
		testfile << "program test(input, output);" << endl;
		testfile << "begin" << endl;
		// print 12.2
		testfile << "   writeln(10.5 * 2);" << endl;
		testfile << "end." << endl;
		
		testfile.close();
		
		FILE* palout = popen("bin/pal -n test/asc/test.pal", "r");
		ASSERT_NE(palout, (void*)0);
		
		float i;
		
		ASSERT_EQ(fscanf(palout, "%f", &i), 1);
		EXPECT_FLOAT_EQ(i, 21.0);
		
		pclose(palout);
	}
	
	TEST(CodegenTest, TestDivideReal)
	{
		ofstream testfile("test/asc/test.pal");
		
		testfile << "program test(input, output);" << endl;
		testfile << "begin" << endl;
		// print 12.2
		testfile << "   writeln(5.0 / 2.5);" << endl;
		testfile << "end." << endl;
		
		testfile.close();
		
		FILE* palout = popen("bin/pal -n test/asc/test.pal", "r");
		ASSERT_NE(palout, (void*)0);
		
		float i;
		
		ASSERT_EQ(fscanf(palout, "%f", &i), 1);
		EXPECT_FLOAT_EQ(i, 2.0);
		
		pclose(palout);
	}
	
	TEST(CodegenTest, TestDivideRealInt)
	{
		ofstream testfile("test/asc/test.pal");
		
		testfile << "program test(input, output);" << endl;
		testfile << "begin" << endl;
		// print 12.2
		testfile << "   writeln(5.0 / 2);" << endl;
		testfile << "end." << endl;
		
		testfile.close();
		
		FILE* palout = popen("bin/pal -n test/asc/test.pal", "r");
		ASSERT_NE(palout, (void*)0);
		
		float i;
		
		ASSERT_EQ(fscanf(palout, "%f", &i), 1);
		EXPECT_FLOAT_EQ(i, 2.5);
		
		pclose(palout);
	}
	
	TEST(CodegenTest, TestDivideIntReal)
	{
		ofstream testfile("test/asc/test.pal");
		
		testfile << "program test(input, output);" << endl;
		testfile << "begin" << endl;
		// print 12.2
		testfile << "   writeln(5 / 2.5);" << endl;
		testfile << "end." << endl;
		
		testfile.close();
		
		FILE* palout = popen("bin/pal -n test/asc/test.pal", "r");
		ASSERT_NE(palout, (void*)0);
		
		float i;
		
		ASSERT_EQ(fscanf(palout, "%f", &i), 1);
		EXPECT_FLOAT_EQ(i, 2.0);
		
		pclose(palout);
	}
	
	TEST(CodegenTest, TestDivideInt)
	{
		ofstream testfile("test/asc/test.pal");
		
		testfile << "program test(input, output);" << endl;
		testfile << "begin" << endl;
		// print 12.2
		testfile << "   writeln(10 div 2);" << endl;
		testfile << "end." << endl;
		
		testfile.close();
		
		FILE* palout = popen("bin/pal -n test/asc/test.pal", "r");
		ASSERT_NE(palout, (void*)0);
		
		int i;
		
		ASSERT_EQ(fscanf(palout, "%i", &i), 1);
		EXPECT_EQ(i, 5);
		
		pclose(palout);
	}
	
	// This test should fail...
	TEST(CodegenTest, TestDivideIntZero)
	{
		ofstream testfile("test/asc/testDivZero.pal");
		
		testfile << "program test(input, output);" << endl;
		testfile << "begin" << endl;
		// print 12.2
		testfile << "   writeln(10 div 0);" << endl;
		testfile << "end." << endl;
		
		testfile.close();
		
		FILE* palout = popen("bin/pal -n -S test/asc/testDivZero.pal", "r");
		ASSERT_NE(palout, (void*)0);
		
		int i;
		
		ASSERT_EQ(fscanf(palout, "%i", &i), 1);
		EXPECT_EQ(i, 5);
		
		pclose(palout);
	}
	// test should fail
	TEST(CodegenTest, TestDivideZero)
	{
		ofstream testfile("test/asc/test.pal");
		
		testfile << "program test(input, output);" << endl;
		testfile << "begin" << endl;
		// print 12.2
		testfile << "   writeln(10 / 0);" << endl;
		testfile << "end." << endl;
		
		testfile.close();
		
		FILE* palout = popen("bin/pal -n test/asc/test.pal", "r");
		ASSERT_NE(palout, (void*)0);
		
		int i;
		
		ASSERT_EQ(fscanf(palout, "%i", &i), 1);
		EXPECT_EQ(i, 5);
		
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

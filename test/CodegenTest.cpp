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
	
	
	TEST(CodegenTest, TestConstantDec)
	{
		ofstream testfile("test/asc/testConst.pal");
		
		testfile << "program test(input, output);" << endl;
		testfile << "const" << endl;
		testfile << "\tx = 1 - 10;" << endl;
		testfile << "\ty = 2.5;" << endl;
		testfile << "\tz = 3.2;" << endl;
		testfile << "begin" << endl;
		testfile << "   writeln(x);" << endl;
		testfile << "   writeln(y);" << endl;
		testfile << "   writeln(z);" << endl;
		testfile << "end." << endl;
		
		testfile.close();
		
		FILE* palout = popen("bin/pal -S -n test/asc/testConst.pal", "r");
		ASSERT_NE(palout, (void*)0);
		
		char str [1000];
		
		fgets(str, 300 , palout);
		EXPECT_STREQ(str, "        -9\n");
		
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
		
		FILE* palout = popen("bin/pal -n test/asc/testDivZero.pal", "r");
		ASSERT_NE(palout, (void*)0);
		
		char str [300];
		fgets(str, 300 , palout);
		EXPECT_STRCASEEQ(str, "Error: Division by zero.\n");
		
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
		
		char str [300];
		fgets(str, 300 , palout);
		EXPECT_STRCASEEQ(str, "Error: Division by zero.\n");
		
		pclose(palout);
	}
	
	// test should fail
	TEST(CodegenTest, TestModZero)
	{
		ofstream testfile("test/asc/test.pal");
		
		testfile << "program test(input, output);" << endl;
		testfile << "begin" << endl;
		// print 12.2
		testfile << "   writeln(10 mod 0);" << endl;
		testfile << "end." << endl;
		
		testfile.close();
		
		FILE* palout = popen("bin/pal -n test/asc/test.pal", "r");
		ASSERT_NE(palout, (void*)0);
		
		char str [300];
		fgets(str, 300 , palout);
		EXPECT_STRCASEEQ(str, "Error: Division by zero.\n");
		
		pclose(palout);
	}
	
	TEST(CodegenTest, TestModInt)
	{
		ofstream testfile("test/asc/test.pal");
		
		testfile << "program test(input, output);" << endl;
		testfile << "begin" << endl;
		// print 12.2
		testfile << "   writeln(10 mod 3);" << endl;
		testfile << "end." << endl;
		
		testfile.close();
		
		FILE* palout = popen("bin/pal -n test/asc/test.pal", "r");
		ASSERT_NE(palout, (void*)0);
		
		int i;
		
		ASSERT_EQ(fscanf(palout, "%i", &i), 1);
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
		EXPECT_FLOAT_EQ(i, 3.14);

		pclose(palout);
	}

	TEST(CodegenTest, TestWriteChar)
	{
		ofstream testfile("test/asc/test.pal");

		testfile << "program test(input, output);" << endl;
		testfile << "begin" << endl;
		testfile << "   writeln('z');" << endl;
		testfile << "   writeln('h', 'e', 'l', 'l', 'o');" << endl;
		testfile << "   write('h');" << endl;
		testfile << "   write('e');" << endl;
		testfile << "   write('l');" << endl;
		testfile << "   write('l');" << endl;
		testfile << "   writeln('o');" << endl;
		testfile << "end." << endl;

		testfile.close();

		FILE* palout = popen("bin/pal -n test/asc/test.pal", "r");
		ASSERT_NE(palout, (void*)0);

		char buf[256];

		ASSERT_EQ(fscanf(palout, "%s", buf), 1);
		EXPECT_EQ(string(buf), "z");

		ASSERT_EQ(fscanf(palout, "%s", buf), 1);
		EXPECT_EQ(string(buf), "hello");

		ASSERT_EQ(fscanf(palout, "%s", buf), 1);
		EXPECT_EQ(string(buf), "hello");

		pclose(palout);
	}

	TEST(CodegenTest, TestWriteString)
	{
		ofstream testfile("test/asc/testWriteLine.pal");

		testfile << "program test(input, output);" << endl;
		testfile << "begin" << endl;
		testfile << "   writeln('hello world');" << endl;
		testfile << "end." << endl;

		testfile.close();

		FILE* palout = popen("bin/pal -n -S  test/asc/testWriteLine.pal", "r");
		ASSERT_NE(palout, (void*)0);

		char* buf = new char[256];
		size_t bufsize = 255;

		ASSERT_GT(getline(&buf, &bufsize, palout), 0);
		EXPECT_EQ(string(buf), "hello world\n"); 

		delete buf;

		pclose(palout);
	}

	TEST(CodegenTest, TestConditional0)
	{
		ofstream testfile("test/asc/test.pal");

		testfile << "program test(input, output);" << endl;
		testfile << "begin" << endl;
		testfile << "  if (1 = 1) then" << endl;
		testfile << "  begin" << endl;
		testfile << "    writeln(1);" << endl;
		testfile << "  end" << endl;
		testfile << "  else" << endl;
		testfile << "  begin" << endl;
		testfile << "    writeln(0);" << endl;
		testfile << "  end" << endl;
		testfile << "end." << endl;

		testfile.close();

		FILE* palout = popen("bin/pal -n -S  test/asc/test.pal", "r");
		ASSERT_NE(palout, (void*)0);

		int i;
		ASSERT_EQ(fscanf(palout, "%d", &i), 1);
		EXPECT_EQ(i, 1);

		pclose(palout);
	}

	TEST(CodegenTest, TestConditional1)
	{
		ofstream testfile("test/asc/test.pal");

		testfile << "program test(input, output);" << endl;
		testfile << "begin" << endl;
		testfile << "  if (1 <> 1) then" << endl;
		testfile << "  begin" << endl;
		testfile << "    writeln(1);" << endl;
		testfile << "  end" << endl;
		testfile << "  else" << endl;
		testfile << "  begin" << endl;
		testfile << "    writeln(0);" << endl;
		testfile << "  end" << endl;
		testfile << "end." << endl;

		testfile.close();

		FILE* palout = popen("bin/pal -n -S  test/asc/test.pal", "r");
		ASSERT_NE(palout, (void*)0);

		int i;
		ASSERT_EQ(fscanf(palout, "%d", &i), 1);
		EXPECT_EQ(i, 0);

		pclose(palout);
	}

	TEST(CodegenTest, TestNestedConditional0)
	{
		ofstream testfile("test/asc/test.pal");

		testfile << "program test(input, output);" << endl;
		testfile << "begin" << endl;
		testfile << "  if (1 = 1) then" << endl;
		testfile << "  begin" << endl;
		testfile << "    if (2 = 2) then" << endl;
		testfile << "    begin" << endl;
		testfile << "      writeln(0);" << endl;
		testfile << "    end" << endl;
		testfile << "    else" << endl;
		testfile << "    begin" << endl;
		testfile << "      writeln(1);" << endl;
		testfile << "    end" << endl;
		testfile << "  end" << endl;
		testfile << "  else" << endl;
		testfile << "  begin" << endl;
		testfile << "    if (3 = 3) then" << endl;
		testfile << "    begin" << endl;
		testfile << "      writeln(2);" << endl;
		testfile << "    end" << endl;
		testfile << "    else" << endl;
		testfile << "    begin" << endl;
		testfile << "      writeln(3);" << endl;
		testfile << "    end" << endl;
		testfile << "  end" << endl;
		testfile << "end." << endl;

		testfile.close();

		FILE* palout = popen("bin/pal -n -S  test/asc/test.pal", "r");
		ASSERT_NE(palout, (void*)0);

		int i;
		ASSERT_EQ(fscanf(palout, "%d", &i), 1);
		EXPECT_EQ(i, 0);

		pclose(palout);
	}

	TEST(CodegenTest, TestNestedConditional1)
	{
		ofstream testfile("test/asc/test.pal");

		testfile << "program test(input, output);" << endl;
		testfile << "begin" << endl;
		testfile << "  if (1 = 1) then" << endl;
		testfile << "  begin" << endl;
		testfile << "    if (2 <> 2) then" << endl;
		testfile << "    begin" << endl;
		testfile << "      writeln(0);" << endl;
		testfile << "    end" << endl;
		testfile << "    else" << endl;
		testfile << "    begin" << endl;
		testfile << "      writeln(1);" << endl;
		testfile << "    end" << endl;
		testfile << "  end" << endl;
		testfile << "  else" << endl;
		testfile << "  begin" << endl;
		testfile << "    if (3 = 3) then" << endl;
		testfile << "    begin" << endl;
		testfile << "      writeln(2);" << endl;
		testfile << "    end" << endl;
		testfile << "    else" << endl;
		testfile << "    begin" << endl;
		testfile << "      writeln(3);" << endl;
		testfile << "    end" << endl;
		testfile << "  end" << endl;
		testfile << "end." << endl;

		testfile.close();

		FILE* palout = popen("bin/pal -n -S  test/asc/test.pal", "r");
		ASSERT_NE(palout, (void*)0);

		int i;
		ASSERT_EQ(fscanf(palout, "%d", &i), 1);
		EXPECT_EQ(i, 1);

		pclose(palout);
	}

	TEST(CodegenTest, TestNestedConditional2)
	{
		ofstream testfile("test/asc/test.pal");

		testfile << "program test(input, output);" << endl;
		testfile << "begin" << endl;
		testfile << "  if (1 <> 1) then" << endl;
		testfile << "  begin" << endl;
		testfile << "    if (2 <> 2) then" << endl;
		testfile << "    begin" << endl;
		testfile << "      writeln(0);" << endl;
		testfile << "    end" << endl;
		testfile << "    else" << endl;
		testfile << "    begin" << endl;
		testfile << "      writeln(1);" << endl;
		testfile << "    end" << endl;
		testfile << "  end" << endl;
		testfile << "  else" << endl;
		testfile << "  begin" << endl;
		testfile << "    if (3 <> 3) then" << endl;
		testfile << "    begin" << endl;
		testfile << "      writeln(2);" << endl;
		testfile << "    end" << endl;
		testfile << "    else" << endl;
		testfile << "    begin" << endl;
		testfile << "      writeln(3);" << endl;
		testfile << "    end" << endl;
		testfile << "  end" << endl;
		testfile << "end." << endl;

		testfile.close();

		FILE* palout = popen("bin/pal -n -S  test/asc/test.pal", "r");
		ASSERT_NE(palout, (void*)0);

		int i;
		ASSERT_EQ(fscanf(palout, "%d", &i), 1);
		EXPECT_EQ(i, 3);

		pclose(palout);
	}

	/* TODO Can't properly test until we have variables and comparisons working fully
	TEST(CodegenTest, TestWhileLoop0)
	{
		ofstream testfile("test/asc/test.pal");

		testfile << "program test(input, output);" << endl;
		testfile << "var i : integer;" << endl;
		testfile << "begin" << endl;
		testfile << "  i := 0;" << endl;
		testfile << "  while (i < 10) do" << endl;
		testfile << "  begin" << endl;
		testfile << "    i := i + 1;" << endl;
		testfile << "    writeln(27);" << endl;
		testfile << "  end" << endl;
		testfile << "end." << endl;

		testfile.close();

		FILE* palout = popen("bin/pal -n -S  test/asc/test.pal", "r");
		ASSERT_NE(palout, (void*)0);

		int val;
		for (int i = 0; i < 10; ++i)
		{
			ASSERT_EQ(fscanf(palout, "%d", &val), 1);
			EXPECT_EQ(val, 27);
		}

		pclose(palout);
	}
	*/

	TEST(CodegenTest, TestProcedure1)
	{
		ofstream testfile("test/asc/test.pal");

		testfile << "program test(input, output);" << endl;
		testfile << "procedure foo();" << endl;
		testfile << "begin" << endl;
		testfile << "  writeln(72)" << endl;
		testfile << "end;" << endl;
		testfile << "begin" << endl;
		testfile << "  foo();" << endl;
		testfile << "end." << endl;

		testfile.close();

		FILE* palout = popen("bin/pal -n -S  test/asc/test.pal", "r");
		ASSERT_NE(palout, (void*)0);

		int val;
		ASSERT_EQ(fscanf(palout, "%d", &val), 1);
		EXPECT_EQ(val, 72);

		pclose(palout);
	}

	TEST(CodegenTest, TestProcedure2)
	{
		ofstream testfile("test/asc/test.pal");

		testfile << "program test(input, output);" << endl;
		testfile << "procedure foo();" << endl;

			testfile << "procedure bar();" << endl;
			testfile << "begin" << endl;
			testfile << "  writeln(72);" << endl;
			testfile << "end;" << endl;

		testfile << "begin" << endl;
		testfile << "  bar();" << endl;
		testfile << "  writeln(24);" << endl;
		testfile << "end;" << endl;

		testfile << "begin" << endl;
		testfile << "  foo();" << endl;
		testfile << "end." << endl;

		testfile.close();

		FILE* palout = popen("bin/pal -n -S  test/asc/test.pal", "r");
		ASSERT_NE(palout, (void*)0);

		int val;
		ASSERT_EQ(fscanf(palout, "%d", &val), 1);
		EXPECT_EQ(val, 72);

		ASSERT_EQ(fscanf(palout, "%d", &val), 1);
		EXPECT_EQ(val, 24);

		pclose(palout);
	}

	TEST(CodegenTest, TestFunction1)
	{
		ofstream testfile("test/asc/test.pal");

		testfile << "program test(input, output);" << endl;
		testfile << "function foo() : integer;" << endl;
		testfile << "begin" << endl;
		testfile << "  foo := 53;" << endl;
		testfile << "end;" << endl;
		testfile << "begin" << endl;
		testfile << "  writeln(foo());" << endl;
		testfile << "end." << endl;

		testfile.close();

		FILE* palout = popen("bin/pal -n -S  test/asc/test.pal", "r");
		ASSERT_NE(palout, (void*)0);

		int val;
		ASSERT_EQ(fscanf(palout, "%d", &val), 1);
		EXPECT_EQ(val, 53);

		pclose(palout);
	}
}

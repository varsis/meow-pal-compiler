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

		delete [] buf;

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
		ofstream testfile("test/asc/testfn.pal");

		testfile << "program test(input, output);" << endl;
		testfile << "function foo() : integer;" << endl;
		testfile << "begin" << endl;
		testfile << "  foo := 53;" << endl;
		testfile << "end;" << endl;
		testfile << "begin" << endl;
		testfile << "  writeln(foo());" << endl;
		testfile << "end." << endl;

		testfile.close();

		FILE* palout = popen("bin/pal -n -S  test/asc/testfn.pal", "r");
		ASSERT_NE(palout, (void*)0);

		int val;
		ASSERT_EQ(fscanf(palout, "%d", &val), 1);
		EXPECT_EQ(val, 53);

		pclose(palout);
	}

	TEST(CodegenTest, TestProcedureArgs)
	{
		ofstream testfile("test/asc/test.pal");

		testfile << "program test(input, output);" << endl;
		testfile << "procedure foo(i : integer);" << endl;
		testfile << "begin" << endl;
		testfile << "  writeln(i);" << endl;
		testfile << "end;" << endl;

		testfile << "begin" << endl;
		testfile << "  foo(23);" << endl;
		testfile << "end." << endl;

		testfile.close();

		FILE* palout = popen("bin/pal -n -S  test/asc/test.pal", "r");
		ASSERT_NE(palout, (void*)0);

		int val;
		ASSERT_EQ(fscanf(palout, "%d", &val), 1);
		EXPECT_EQ(val, 23);

		pclose(palout);
	}

	TEST(CodegenTest, TestProcedureArgs2)
	{
		ofstream testfile("test/asc/test.pal");

		testfile << "program test(input, output);" << endl;
		testfile << "procedure foo(i : integer; j : integer);" << endl;
		testfile << "begin" << endl;
		testfile << "  writeln(i);" << endl;
		testfile << "  writeln(j);" << endl;
		testfile << "end;" << endl;

		testfile << "begin" << endl;
		testfile << "  foo(23, 25);" << endl;
		testfile << "end." << endl;

		testfile.close();

		FILE* palout = popen("bin/pal -n -S  test/asc/test.pal", "r");
		ASSERT_NE(palout, (void*)0);

		int val;
		ASSERT_EQ(fscanf(palout, "%d", &val), 1);
		EXPECT_EQ(val, 23);

		ASSERT_EQ(fscanf(palout, "%d", &val), 1);
		EXPECT_EQ(val, 25);

		pclose(palout);
	}

	TEST(CodegenTest, TestFunctionArgs)
	{
		ofstream testfile("test/asc/testfnargs.pal");

		testfile << "program test(input, output);" << endl;
		testfile << "function foo(i : integer; j : integer) : integer;" << endl;
		testfile << "begin" << endl;
		testfile << "  writeln(i);" << endl;
		testfile << "  writeln(j);" << endl;
		testfile << "  foo := i + j;" << endl;
		testfile << "end;" << endl;

		testfile << "begin" << endl;
		testfile << "  writeln(foo(23, 25));" << endl;
		testfile << "end." << endl;

		testfile.close();

		FILE* palout = popen("bin/pal -n -S  test/asc/testfnargs.pal", "r");
		ASSERT_NE(palout, (void*)0);

		int val;
		ASSERT_EQ(fscanf(palout, "%d", &val), 1);
		EXPECT_EQ(val, 23);

		ASSERT_EQ(fscanf(palout, "%d", &val), 1);
		EXPECT_EQ(val, 25);

		ASSERT_EQ(fscanf(palout, "%d", &val), 1);
		EXPECT_EQ(val, 48);

		pclose(palout);
	}

	TEST(CodegenTest, TestVariables)
	{
		ofstream testfile("test/asc/test.pal");

		testfile << "program test(input, output);" << endl;
		testfile << "var" << endl;
		testfile << "	a : integer;" << endl;
		testfile << "begin" << endl;
		testfile << "  a := 5;" << endl;
		testfile << "  writeln(a + 3);" << endl;
		testfile << "end." << endl;

		testfile.close();

		FILE* palout = popen("bin/pal -n -S  test/asc/test.pal", "r");
		ASSERT_NE(palout, (void*)0);

		int val;
		ASSERT_EQ(fscanf(palout, "%d", &val), 1);
		EXPECT_EQ(val, 8);

		pclose(palout);
	}

	TEST(CodegenTest, TestVariables2)
	{
		ofstream testfile("test/asc/test.pal");

		testfile << "program test(input, output);" << endl;
		testfile << "var" << endl;
		testfile << "	a, b : integer;" << endl;
		testfile << "begin" << endl;
		testfile << "  a := 1;" << endl;
		testfile << "  b := 2;" << endl;
		testfile << "  writeln(a);" << endl;
		testfile << "  writeln(b);" << endl;
		testfile << "  writeln(a + b);" << endl;
		testfile << "end." << endl;

		testfile.close();

		FILE* palout = popen("bin/pal -n -S  test/asc/test.pal", "r");
		ASSERT_NE(palout, (void*)0);

		int val;
		ASSERT_EQ(fscanf(palout, "%d", &val), 1);
		EXPECT_EQ(val, 1);

		ASSERT_EQ(fscanf(palout, "%d", &val), 1);
		EXPECT_EQ(val, 2);

		ASSERT_EQ(fscanf(palout, "%d", &val), 1);
		EXPECT_EQ(val, 3);

		pclose(palout);
	}

	TEST(CodegenTest, TestRecord)
	{
		ofstream testfile("test/asc/testrecord.pal");

		testfile << "program test(input, output);" << endl;
		testfile << "type" << endl;
		testfile << "	recordType = record a : integer; end;" << endl;
		testfile << "var" << endl;
		testfile << "	aRecord : recordType;" << endl;
		testfile << "begin" << endl;
		testfile << "  aRecord.a := 55;" << endl;
		testfile << "  writeln(aRecord.a);" << endl;
		testfile << "end." << endl;

		testfile.close();

		FILE* palout = popen("bin/pal -n -S  test/asc/testrecord.pal", "r");
		ASSERT_NE(palout, (void*)0);

		int val;
		ASSERT_EQ(fscanf(palout, "%d", &val), 1);
		EXPECT_EQ(val, 55);

		pclose(palout);
	}

	TEST(CodegenTest, TestRecord2)
	{
		ofstream testfile("test/asc/testrecord.pal");

		testfile << "program test(input, output);" << endl;
		testfile << "type" << endl;
		testfile << "	recordType = record a : integer; b : integer; c : integer; end;" << endl;
		testfile << "var" << endl;
		testfile << "	aRecord : recordType;" << endl;
		testfile << "begin" << endl;
		testfile << "  aRecord.c := 1;" << endl;
		testfile << "  aRecord.a := 2;" << endl;
		testfile << "  aRecord.b := 3;" << endl;
		testfile << "  writeln(aRecord.a);" << endl;
		testfile << "  writeln(aRecord.b);" << endl;
		testfile << "  writeln(aRecord.c);" << endl;
		testfile << "end." << endl;

		testfile.close();

		FILE* palout = popen("bin/pal -n -S  test/asc/testrecord.pal", "r");
		ASSERT_NE(palout, (void*)0);

		int val;
		ASSERT_EQ(fscanf(palout, "%d", &val), 1);
		EXPECT_EQ(2, val);
		ASSERT_EQ(fscanf(palout, "%d", &val), 1);
		EXPECT_EQ(3, val);
		ASSERT_EQ(fscanf(palout, "%d", &val), 1);
		EXPECT_EQ(1, val);

		pclose(palout);
	}

	TEST(CodegenTest, TestRecord3)
	{
		ofstream testfile("test/asc/testrecord.pal");

		testfile << "program test(input, output);" << endl;
		testfile << "type" << endl;
		testfile << "	r1 = record a : integer; b : integer; end;" << endl;
		testfile << "	r2 = record x : integer; y : r1; end;" << endl;
		testfile << "var" << endl;
		testfile << "	r : r2;" << endl;
		testfile << "begin" << endl;
		testfile << "  r.x := 32;" << endl;
		testfile << "  r.y.a := 11;" << endl;
		testfile << "  r.y.b := 22;" << endl;
		testfile << "  writeln(r.x);" << endl;
		testfile << "  writeln(r.y.a);" << endl;
		testfile << "  writeln(r.y.b);" << endl;
		testfile << "end." << endl;

		testfile.close();

		FILE* palout = popen("bin/pal -n -S  test/asc/testrecord.pal", "r");
		ASSERT_NE(palout, (void*)0);

		int val;
		ASSERT_EQ(fscanf(palout, "%d", &val), 1);
		EXPECT_EQ(32, val);
		ASSERT_EQ(fscanf(palout, "%d", &val), 1);
		EXPECT_EQ(11, val);
		ASSERT_EQ(fscanf(palout, "%d", &val), 1);
		EXPECT_EQ(22, val);

		pclose(palout);
	}
	
	TEST(CodegenTest, TestRecordCopy)
	{
		ofstream testfile("test/asc/testrecord.pal");

		testfile << "program test(input, output);" << endl;
		testfile << "type" << endl;
		testfile << "	recordType = record a : integer; end;" << endl;
		testfile << "var" << endl;
		testfile << "	r1 : recordType;" << endl;
		testfile << "	r2 : recordType;" << endl;
		testfile << "begin" << endl;
		testfile << "  r2.a := 125;" << endl;
		testfile << "  writeln(r2.a);" << endl;
		testfile << "  r1.a := 55;" << endl;
		testfile << "  r2 := r1;" << endl;
		testfile << "  writeln(r2.a);" << endl;
		testfile << "end." << endl;

		testfile.close();

		FILE* palout = popen("bin/pal -n -S  test/asc/testrecord.pal", "r");
		ASSERT_NE(palout, (void*)0);

		int val;
		ASSERT_EQ(fscanf(palout, "%d", &val), 1);
		EXPECT_EQ(val, 125);
		ASSERT_EQ(fscanf(palout, "%d", &val), 1);
		EXPECT_EQ(val, 55);

		pclose(palout);
	}

	TEST(CodegenTest, TestRecordCopy2)
	{
		ofstream testfile("test/asc/testrecord.pal");

		testfile << "program test(input, output);" << endl;
		testfile << "type" << endl;
		testfile << "	recordType = record a : integer; b : integer; end;" << endl;
		testfile << "var" << endl;
		testfile << "	r1 : recordType;" << endl;
		testfile << "	r2 : recordType;" << endl;
		testfile << "begin" << endl;
		testfile << "  r2.a := 1;" << endl;
		testfile << "  r2.b := 2;" << endl;
		testfile << "  writeln(r2.a);" << endl;
		testfile << "  writeln(r2.b);" << endl;
		testfile << "  r1.a := 11;" << endl;
		testfile << "  r1.b := 22;" << endl;
		testfile << "  r2 := r1;" << endl;
		testfile << "  writeln(r2.a);" << endl;
		testfile << "  writeln(r2.b);" << endl;
		testfile << "end." << endl;

		testfile.close();

		FILE* palout = popen("bin/pal -n -S  test/asc/testrecord.pal", "r");
		ASSERT_NE(palout, (void*)0);

		int val;
		ASSERT_EQ(fscanf(palout, "%d", &val), 1);
		EXPECT_EQ(val, 1);
		ASSERT_EQ(fscanf(palout, "%d", &val), 1);
		EXPECT_EQ(val, 2);
		ASSERT_EQ(fscanf(palout, "%d", &val), 1);
		EXPECT_EQ(val, 11);
		ASSERT_EQ(fscanf(palout, "%d", &val), 1);
		EXPECT_EQ(val, 22);
		pclose(palout);
	}
}

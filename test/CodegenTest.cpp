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

	TEST(CodegenTest, TestEnum)
	{
		ofstream testfile("test/asc/testEnum.pal");
		
		testfile << "program test(input, output);" << endl;
		testfile << "type t = (hey, man, sup);" << endl;
		testfile << "var a : t;" << endl;
		testfile << "begin" << endl;
		testfile << "   a := hey;" << endl;
		testfile << "   if (a = hey) then" << endl;
		testfile << "	begin" << endl;
		testfile << "		writeln(1);" << endl;
		testfile << "	end" << endl;
		testfile << "	else" << endl;
		testfile << "	begin" << endl;
		testfile << "		writeln(2);" << endl;
		testfile << "	end" << endl;
		testfile << "end." << endl;
		
		testfile.close();
		
		FILE* palout = popen("bin/pal -S -n test/asc/testEnum.pal", "r");
		
		ASSERT_NE(palout, (void*)0);
		
		int i;
		
		ASSERT_EQ(fscanf(palout, "%d", &i), 1);
		EXPECT_EQ(i, 1);
		
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
		testfile << "function foo(i : integer) : integer;" << endl;
		testfile << "begin" << endl;
		testfile << "  writeln(i);" << endl;
		testfile << "  foo := i;" << endl;
		testfile << "end;" << endl;
		testfile << "begin" << endl;
		testfile << "  writeln(foo(23));" << endl;
		testfile << "end." << endl;

		testfile.close();

		FILE* palout = popen("bin/pal -n -S  test/asc/testfnargs.pal", "r");
		ASSERT_NE(palout, (void*)0);

		int val;
		ASSERT_EQ(fscanf(palout, "%d", &val), 1);
		EXPECT_EQ(val, 23);

		ASSERT_EQ(fscanf(palout, "%d", &val), 1);
		EXPECT_EQ(val, 23);

		pclose(palout);
	}

	TEST(CodegenTest, TestFunctionArgs2)
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
		ofstream testfile("test/asc/testrecord3.pal");

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

		FILE* palout = popen("bin/pal -n -S  test/asc/testrecord3.pal", "r");
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
		ofstream testfile("test/asc/testrecordcp2.pal");

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

		FILE* palout = popen("bin/pal -n -S  test/asc/testrecordcp2.pal", "r");
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

	TEST(CodegenTest, TestRecordArg)
	{
		ofstream testfile("test/asc/testrecordarg.pal");

		testfile << "program test(input, output);" << endl;
		testfile << "type" << endl;
		testfile << "	recordType = record a : integer; b : integer; end;" << endl;
		testfile << "var" << endl;
		testfile << "	r1 : recordType;" << endl;
		testfile << "procedure foo(r : recordType);" << endl;
		testfile << "begin" << endl;
		testfile << "	writeln(r.a);" << endl;
		testfile << "	writeln(r.b);" << endl;
		testfile << "end;" << endl;
		testfile << "begin" << endl;
		testfile << "  r1.a := 11;" << endl;
		testfile << "  r1.b := 22;" << endl;
		testfile << "  foo(r1);" << endl;
		testfile << "end." << endl;

		testfile.close();

		FILE* palout = popen("bin/pal -n -S  test/asc/testrecordarg.pal", "r");
		ASSERT_NE(palout, (void*)0);

		int val;
		ASSERT_EQ(fscanf(palout, "%d", &val), 1);
		EXPECT_EQ(val, 11);
		ASSERT_EQ(fscanf(palout, "%d", &val), 1);
		EXPECT_EQ(val, 22);
		pclose(palout);
	}

	TEST(CodegenTest, TestRecordArg2)
	{
		ofstream testfile("test/asc/testrecordarg.pal");

		testfile << "program test(input, output);" << endl;
		testfile << "type" << endl;
		testfile << "	recordType1 = record a : integer; b : integer; end;" << endl;
		testfile << "	recordType2 = record x : recordType1; y : recordType1; end;" << endl;
		testfile << "var" << endl;
		testfile << "	r : recordType2;" << endl;
		testfile << "procedure foo(arg : recordType2);" << endl;
		testfile << "begin" << endl;
		testfile << "	writeln(arg.x.a);" << endl;
		testfile << "	writeln(arg.x.b);" << endl;
		testfile << "	writeln(arg.y.a);" << endl;
		testfile << "	writeln(arg.y.b);" << endl;
		testfile << "end;" << endl;
		testfile << "begin" << endl;
		testfile << "  r.x.a := 11;" << endl;
		testfile << "  r.x.b := 22;" << endl;
		testfile << "  r.y.a := 33;" << endl;
		testfile << "  r.y.b := 44;" << endl;
		testfile << "  foo(r);" << endl;
		testfile << "end." << endl;

		testfile.close();

		FILE* palout = popen("bin/pal -n -S  test/asc/testrecordarg.pal", "r");
		ASSERT_NE(palout, (void*)0);

		int val;
		ASSERT_EQ(fscanf(palout, "%d", &val), 1);
		EXPECT_EQ(val, 11);
		ASSERT_EQ(fscanf(palout, "%d", &val), 1);
		EXPECT_EQ(val, 22);
		ASSERT_EQ(fscanf(palout, "%d", &val), 1);
		EXPECT_EQ(val, 33);
		ASSERT_EQ(fscanf(palout, "%d", &val), 1);
		EXPECT_EQ(val, 44);
		pclose(palout);
	}

	TEST(CodegenTest, TestRecordArg3)
	{
		ofstream testfile("test/asc/testrecordarg.pal");

		testfile << "program test(input, output);" << endl;
		testfile << "type" << endl;
		testfile << "	recordType1 = record a : integer; b : integer; end;" << endl;
		testfile << "	recordType2 = record x : recordType1; y : recordType1; end;" << endl;
		testfile << "var" << endl;
		testfile << "	r : recordType2;" << endl;
		testfile << "procedure foo(arg1 : recordType1; arg2 : recordType1);" << endl;
		testfile << "begin" << endl;
		testfile << "	writeln(arg1.a);" << endl;
		testfile << "	writeln(arg1.b);" << endl;
		testfile << "	writeln(arg2.a);" << endl;
		testfile << "	writeln(arg2.b);" << endl;
		testfile << "end;" << endl;
		testfile << "begin" << endl;
		testfile << "  r.x.a := 11;" << endl;
		testfile << "  r.x.b := 22;" << endl;
		testfile << "  r.y.a := 33;" << endl;
		testfile << "  r.y.b := 44;" << endl;
		testfile << "  foo(r.x, r.y);" << endl;
		testfile << "end." << endl;

		testfile.close();

		FILE* palout = popen("bin/pal -n -S  test/asc/testrecordarg.pal", "r");
		ASSERT_NE(palout, (void*)0);

		int val;
		ASSERT_EQ(fscanf(palout, "%d", &val), 1);
		EXPECT_EQ(val, 11);
		ASSERT_EQ(fscanf(palout, "%d", &val), 1);
		EXPECT_EQ(val, 22);
		ASSERT_EQ(fscanf(palout, "%d", &val), 1);
		EXPECT_EQ(val, 33);
		ASSERT_EQ(fscanf(palout, "%d", &val), 1);
		EXPECT_EQ(val, 44);
		pclose(palout);
	}

	TEST(CodegenTest, TestRecordReturn)
	{
		ofstream testfile("test/asc/testrecordret.pal");

		testfile << "program test(input, output);" << endl;
		testfile << "type" << endl;
		testfile << "	recordType1 = record a : integer; b : integer; end;" << endl;
		testfile << "var" << endl;
		testfile << "	r : recordType1;" << endl;
		testfile << "function foo() : recordType1;" << endl;
		testfile << "begin" << endl;
		testfile << "	foo.a := 11;" << endl;
		testfile << "	foo.b := 22;" << endl;
		testfile << "end;" << endl;
		testfile << "begin" << endl;
		testfile << "  r := foo();" << endl;
		testfile << "  writeln(r.a);" << endl;
		testfile << "  writeln(r.b);" << endl;
		testfile << "end." << endl;

		testfile.close();

		FILE* palout = popen("bin/pal -n -S  test/asc/testrecordret.pal", "r");
		ASSERT_NE(palout, (void*)0);

		int val;
		ASSERT_EQ(fscanf(palout, "%d", &val), 1);
		EXPECT_EQ(val, 11);
		ASSERT_EQ(fscanf(palout, "%d", &val), 1);
		EXPECT_EQ(val, 22);
		pclose(palout);
	}

	TEST(CodegenTest, TestRecordReturn2)
	{
		ofstream testfile("test/asc/testrecordret.pal");

		testfile << "program test(input, output);" << endl;
		testfile << "type" << endl;
		testfile << "	recordType1 = record a : integer; b : integer; end;" << endl;
		testfile << "var" << endl;
		testfile << "	r, s, t : recordType1;" << endl;
		testfile << "function foo(x : recordType1; y : recordType1) : recordType1;" << endl;
		testfile << "begin" << endl;
		testfile << "	foo.a := x.a + y.a;" << endl;
		testfile << "	foo.b := x.b + y.b;" << endl;
		testfile << "end;" << endl;
		testfile << "begin" << endl;
		testfile << "  s.a := 1;" << endl;
		testfile << "  s.b := 2;" << endl;
		testfile << "  t.a := 3;" << endl;
		testfile << "  t.b := 4;" << endl;
		testfile << "  r := foo(s, t);" << endl;
		testfile << "  writeln(r.a);" << endl;
		testfile << "  writeln(r.b);" << endl;
		testfile << "end." << endl;

		testfile.close();

		FILE* palout = popen("bin/pal -n -S  test/asc/testrecordret.pal", "r");
		ASSERT_NE(palout, (void*)0);

		int val;
		ASSERT_EQ(fscanf(palout, "%d", &val), 1);
		EXPECT_EQ(val, 4);
		ASSERT_EQ(fscanf(palout, "%d", &val), 1);
		EXPECT_EQ(val, 6);
		pclose(palout);
	}

	TEST(CodegenTest, TestRecordReturn3)
	{
		ofstream testfile("test/asc/test.pal");

		testfile << "program test(input, output);" << endl;
		testfile << "type" << endl;
		testfile << "	rt1 = record a : integer; b : integer; end;" << endl;
		testfile << "	rt2 = record a : rt1; b : rt1; end;" << endl;
		testfile << "var" << endl;
		testfile << "	s, t: rt1;" << endl;
		testfile << "	r : rt2;" << endl;
		testfile << "function foo(x : rt1; y : rt1) : rt2;" << endl;
		testfile << "begin" << endl;
		testfile << "	foo.a := x;" << endl;
		testfile << "	foo.b := y;" << endl;
		testfile << "end;" << endl;
		testfile << "begin" << endl;
		testfile << "  s.a := 1;" << endl;
		testfile << "  s.b := 2;" << endl;
		testfile << "  t.a := 3;" << endl;
		testfile << "  t.b := 4;" << endl;
		testfile << "  r := foo(s, t);" << endl;
		testfile << "  writeln(r.a.a);" << endl;
		testfile << "  writeln(r.a.b);" << endl;
		testfile << "  writeln(r.b.a);" << endl;
		testfile << "  writeln(r.b.b);" << endl;
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
		ASSERT_EQ(fscanf(palout, "%d", &val), 1);
		EXPECT_EQ(val, 4);
		pclose(palout);
	}

	TEST(CodegenTest, TestVarParam1)
	{
		ofstream testfile("test/asc/varparm1.pal");

		testfile << "program test(input, output);" << endl;
		testfile << "var i : integer;" << endl;
		testfile << "procedure foo(var x : integer);" << endl;
		testfile << "begin" << endl;
		testfile << "	x := 69;" << endl; // HAHAHA 69 IS A DIRRTY NUMBER LOLLLLLLL
		testfile << "end;" << endl;
		testfile << "begin" << endl;
		testfile << "  foo(i);" << endl;
		testfile << "  writeln(i);" << endl;
		testfile << "end." << endl;

		testfile.close();

		FILE* palout = popen("bin/pal -n -S  test/asc/varparm1.pal", "r");
		ASSERT_NE(palout, (void*)0);

		int val;
		ASSERT_EQ(fscanf(palout, "%d", &val), 1);
		EXPECT_EQ(val, 69);
		pclose(palout);
	}


	TEST(CodegenTest, TestVarParam2)
	{
		ofstream testfile("test/asc/varparm.pal");

		testfile << "program test(input, output);" << endl;
		testfile << "var i, j, k : integer;" << endl;
		testfile << "procedure foo(var x : integer; y : integer; var z : integer);" << endl;
		testfile << "begin" << endl;
		testfile << "	x := x + y + z;" << endl;
		testfile << "	y := x + y + z;" << endl;
		testfile << "	z := x + y + z;" << endl;
		testfile << "end;" << endl;
		testfile << "begin" << endl;
		testfile << "  i := 1;" << endl;
		testfile << "  j := 1;" << endl;
		testfile << "  k := 1;" << endl;
		testfile << "  foo(i, j, k);" << endl;
		testfile << "  writeln(i);" << endl;
		testfile << "  writeln(j);" << endl;
		testfile << "  writeln(k);" << endl;
		testfile << "end." << endl;

		testfile.close();

		FILE* palout = popen("bin/pal -n -S  test/asc/varparm.pal", "r");
		ASSERT_NE(palout, (void*)0);

		int val;
		ASSERT_EQ(fscanf(palout, "%d", &val), 1);
		EXPECT_EQ(val, 3);
		ASSERT_EQ(fscanf(palout, "%d", &val), 1);
		EXPECT_EQ(val, 1);
		ASSERT_EQ(fscanf(palout, "%d", &val), 1);
		EXPECT_EQ(val, 9);
		pclose(palout);
	}

	TEST(CodegenTest, TestVarParam3)
	{
		ofstream testfile("test/asc/varparm3.pal");

		testfile << "program test(input, output);" << endl;
		testfile << "type" << endl;
		testfile << "	rt = record a : integer; b : integer; end;" << endl;
		testfile << "var" << endl;
		testfile << "	r : rt;" << endl;
		testfile << "procedure foo(var x : rt);" << endl;
		testfile << "begin" << endl;
		testfile << "	x.a := 69;" << endl;
		testfile << "	x.b := 96;" << endl;
		testfile << "end;" << endl;
		testfile << "begin" << endl;
		testfile << "  foo(r);" << endl;
		testfile << "  writeln(r.a);" << endl;
		testfile << "  writeln(r.b);" << endl;
		testfile << "end." << endl;

		testfile.close();

		FILE* palout = popen("bin/pal -n -S  test/asc/varparm3.pal", "r");
		ASSERT_NE(palout, (void*)0);

		int val;
		ASSERT_EQ(fscanf(palout, "%d", &val), 1);
		EXPECT_EQ(val, 69);
		ASSERT_EQ(fscanf(palout, "%d", &val), 1);
		EXPECT_EQ(val, 96);
		pclose(palout);
	}

	TEST(CodegenTest, TestVarParam4)
	{
		ofstream testfile("test/asc/varparm4.pal");

		testfile << "program test(input, output);" << endl;
		testfile << "type" << endl;
		testfile << "	rt = record a : integer; b : integer; end;" << endl;
		testfile << "var" << endl;
		testfile << "	r1, r2 : rt;" << endl;
		testfile << "function foo(var x : rt) : rt;" << endl;
		testfile << "begin" << endl;
		testfile << "	x.a := 69;" << endl;
		testfile << "	x.b := 96;" << endl;
		testfile << "	foo := x;" << endl;
		testfile << "end;" << endl;
		testfile << "begin" << endl;
		testfile << "  r2 := foo(r1);" << endl;
		testfile << "  writeln(r1.a);" << endl;
		testfile << "  writeln(r1.b);" << endl;
		testfile << "  writeln(r2.a);" << endl;
		testfile << "  writeln(r2.b);" << endl;
		testfile << "end." << endl;

		testfile.close();

		FILE* palout = popen("bin/pal -n -S  test/asc/varparm4.pal", "r");
		ASSERT_NE(palout, (void*)0);

		int val;
		ASSERT_EQ(fscanf(palout, "%d", &val), 1);
		EXPECT_EQ(val, 69);
		ASSERT_EQ(fscanf(palout, "%d", &val), 1);
		EXPECT_EQ(val, 96);
		ASSERT_EQ(fscanf(palout, "%d", &val), 1);
		EXPECT_EQ(val, 69);
		ASSERT_EQ(fscanf(palout, "%d", &val), 1);
		EXPECT_EQ(val, 96);
		pclose(palout);
	}

	TEST(CodegenTest, TestVarParam5)
	{
		ofstream testfile("test/asc/varparm.pal");

		testfile << "program test(input, output);" << endl;
		testfile << "type" << endl;
		testfile << "	rt = record a : integer; b : integer; end;" << endl;
		testfile << "var" << endl;
		testfile << "	r1, r2 : rt;" << endl;
		testfile << "function foo(var x : rt) : rt;" << endl;
			testfile << "procedure bar(var y : rt);" << endl;
			testfile << "begin" << endl;
			testfile << "	y.a := 69;" << endl;
			testfile << "	y.b := 96;" << endl;
			testfile << "end;" << endl;
		testfile << "begin" << endl;
		testfile << "	bar(x);" << endl;
		testfile << "	foo := x;" << endl;
		testfile << "end;" << endl;
		testfile << "begin" << endl;
		testfile << "  r2 := foo(r1);" << endl;
		testfile << "  writeln(r1.a);" << endl;
		testfile << "  writeln(r1.b);" << endl;
		testfile << "  writeln(r2.a);" << endl;
		testfile << "  writeln(r2.b);" << endl;
		testfile << "end." << endl;

		testfile.close();

		FILE* palout = popen("bin/pal -n -S  test/asc/varparm.pal", "r");
		ASSERT_NE(palout, (void*)0);

		int val;
		ASSERT_EQ(fscanf(palout, "%d", &val), 1);
		EXPECT_EQ(val, 69);
		ASSERT_EQ(fscanf(palout, "%d", &val), 1);
		EXPECT_EQ(val, 96);
		ASSERT_EQ(fscanf(palout, "%d", &val), 1);
		EXPECT_EQ(val, 69);
		ASSERT_EQ(fscanf(palout, "%d", &val), 1);
		EXPECT_EQ(val, 96);
		pclose(palout);
	}

	TEST(CodegenTest, TestVarParamArray)
	{
		ofstream testfile("test/asc/varparmarray.pal");

		testfile << "program test(input, output);" << endl;
		testfile << "type arr = array[1 .. 10] of integer;" << endl;
		testfile << "var a : arr;" << endl;
		testfile << "procedure foo(var x : integer);" << endl;
		testfile << "begin" << endl;
		//testfile << "	writeln(x);" << endl;
		testfile << "	x := 111;" << endl;
		testfile << "end;" << endl;
		testfile << "begin" << endl;
		//testfile << "	a[5] := 69;" << endl;
		testfile << "	foo(a[5]);" << endl;
		testfile << "	writeln(a[5]);" << endl;
		testfile << "end." << endl;

		testfile.close();

		FILE* palout = popen("bin/pal -n -S  test/asc/varparmarray.pal", "r");
		ASSERT_NE(palout, (void*)0);

		int val;
		//ASSERT_EQ(fscanf(palout, "%d", &val), 1);
		//EXPECT_EQ(val, 69);
		ASSERT_EQ(fscanf(palout, "%d", &val), 1);
		EXPECT_EQ(val, 111);
		pclose(palout);
	}

	TEST(CodegenTest, TestArrays1)
	{
		ofstream testfile("test/asc/array1.pal");

		testfile << "program test(input, output);" << endl;
		testfile << "var" << endl;
		testfile << "	a : array[1 .. 10] of integer;" << endl;
		testfile << "begin" << endl;
		testfile << "	a[5] := 69;" << endl;
		testfile << "	writeln(a[5]);" << endl;
		testfile << "end." << endl;

		testfile.close();

		FILE* palout = popen("bin/pal -n -S  test/asc/array1.pal", "r");
		ASSERT_NE(palout, (void*)0);

		int val;
		ASSERT_EQ(fscanf(palout, "%d", &val), 1);
		EXPECT_EQ(val, 69);
		pclose(palout);
	}

	TEST(CodegenTest, TestArrays2)
	{
		ofstream testfile("test/asc/array2.pal");

		testfile << "program test(input, output);" << endl;
		testfile << "var" << endl;
		testfile << "	i : integer;" << endl;
		testfile << "	a : array[1 .. 10] of integer;" << endl;
		testfile << "begin" << endl;
		testfile << "	i := 5;" << endl;
		testfile << "	a[i] := 10;" << endl;
		testfile << "	a[i+1] := 20;" << endl;
		testfile << "	a[i+2] := a[i] + a[i+1];" << endl;
		testfile << "	writeln(a[i+2]);" << endl;
		testfile << "end." << endl;

		testfile.close();

		FILE* palout = popen("bin/pal -n -S  test/asc/array2.pal", "r");
		ASSERT_NE(palout, (void*)0);

		int val;
		ASSERT_EQ(fscanf(palout, "%d", &val), 1);
		EXPECT_EQ(val, 30);
		pclose(palout);
	}

	TEST(CodegenTest, TestArrays3)
	{
		ofstream testfile("test/asc/array3.pal");

		testfile << "program test(input, output);" << endl;
		testfile << "var" << endl;
		testfile << "	a : array[1 .. 10] of array[1..10] of integer;" << endl;
		testfile << "begin" << endl;
		testfile << "	a[5][5] := 69;" << endl;
		testfile << "	writeln(a[5][5]);" << endl;
		testfile << "end." << endl;

		testfile.close();

		FILE* palout = popen("bin/pal -n -S  test/asc/array3.pal", "r");
		ASSERT_NE(palout, (void*)0);

		int val;
		ASSERT_EQ(fscanf(palout, "%d", &val), 1);
		EXPECT_EQ(val, 69);
		pclose(palout);
	}

	TEST(CodegenTest, TestArrays4)
	{
		ofstream testfile("test/asc/arrays.pal");

		testfile << "program test(input, output);" << endl;
		testfile << "var" << endl;
		testfile << "	i : integer;" << endl;
		testfile << "	a : array[1 .. 10] of array[1..10] of integer;" << endl;
		testfile << "begin" << endl;
		testfile << "	i := 5;" << endl;
		testfile << "	a[i,i] := 69;" << endl;
		testfile << "	writeln(a[i,i]);" << endl;
		testfile << "end." << endl;

		testfile.close();

		FILE* palout = popen("bin/pal -n -S  test/asc/arrays.pal", "r");
		ASSERT_NE(palout, (void*)0);

		int val;
		ASSERT_EQ(fscanf(palout, "%d", &val), 1);
		EXPECT_EQ(val, 69);
		pclose(palout);
	}

	TEST(CodegenTest, TestArrays5)
	{
		ofstream testfile("test/asc/array5.pal");

		testfile << "program test(input, output);" << endl;
		testfile << "var" << endl;
		testfile << "	a : array[100 .. 110] of integer;" << endl;
		testfile << "begin" << endl;
		testfile << "	a[100] := 69;" << endl;
		testfile << "	writeln(a[100]);" << endl;
		testfile << "end." << endl;

		testfile.close();

		FILE* palout = popen("bin/pal -n -S  test/asc/array5.pal", "r");
		ASSERT_NE(palout, (void*)0);

		int val;
		ASSERT_EQ(fscanf(palout, "%d", &val), 1);
		EXPECT_EQ(val, 69);
		pclose(palout);
	}

	TEST(CodegenTest, TestArrays6)
	{
		ofstream testfile("test/asc/arrays.pal");

		testfile << "program test(input, output);" << endl;
		testfile << "var" << endl;
		testfile << "	a : array[1 .. 3] of array[1..3] of integer;" << endl;
		testfile << "begin" << endl;
		testfile << "	a[3][3] := 69;" << endl;
		testfile << "	writeln(10 + a[3][3]);" << endl;
		testfile << "end." << endl;

		testfile.close();

		FILE* palout = popen("bin/pal -n -S  test/asc/arrays.pal", "r");
		ASSERT_NE(palout, (void*)0);

		int val;
		ASSERT_EQ(fscanf(palout, "%d", &val), 1);
		EXPECT_EQ(val, 79);
		pclose(palout);
	}

	TEST(CodegenTest, TestArrays7)
	{
		ofstream testfile("test/asc/arrays.pal");

		testfile << "program test(input, output);" << endl;
		testfile << "var" << endl;
		testfile << "	a : array[1 .. 3] of array[1..3] of integer;" << endl;
		testfile << "begin" << endl;
		testfile << "	a[2,2] := 11;" << endl;
		testfile << "	a[2,3] := 22;" << endl;
		testfile << "	a[3,2] := 33;" << endl;
		testfile << "	a[3,3] := 44;" << endl;
		testfile << "	writeln(a[2,2]);" << endl;
		testfile << "	writeln(a[2,3]);" << endl;
		testfile << "	writeln(a[3,2]);" << endl;
		testfile << "	writeln(a[3,3]);" << endl;
		testfile << "end." << endl;

		testfile.close();

		FILE* palout = popen("bin/pal -n -S  test/asc/arrays.pal", "r");
		ASSERT_NE(palout, (void*)0);

		int val;
		ASSERT_EQ(fscanf(palout, "%d", &val), 1);
		EXPECT_EQ(val, 11);
		ASSERT_EQ(fscanf(palout, "%d", &val), 1);
		EXPECT_EQ(val, 22);
		ASSERT_EQ(fscanf(palout, "%d", &val), 1);
		EXPECT_EQ(val, 33);
		ASSERT_EQ(fscanf(palout, "%d", &val), 1);
		EXPECT_EQ(val, 44);
		pclose(palout);
	}

	TEST(CodegenTest, TestArrays8)
	{
		ofstream testfile("test/asc/arrays.pal");

		testfile << "program test(input, output);" << endl;
		testfile << "var" << endl;
		testfile << "	a : array[1 .. 3] of array[1..4] of array[1..5] of integer;" << endl;
		testfile << "begin" << endl;
		testfile << "	a[2,2,2] := 11;" << endl;
		testfile << "	a[2,2,3] := 22;" << endl;
		testfile << "	a[2,3,2] := 33;" << endl;
		testfile << "	a[2,3,3] := 44;" << endl;
		testfile << "	writeln(a[2,2,2]);" << endl;
		testfile << "	writeln(a[2,2,3]);" << endl;
		testfile << "	writeln(a[2,3,2]);" << endl;
		testfile << "	writeln(a[2,3,3]);" << endl;
		testfile << "end." << endl;

		testfile.close();

		FILE* palout = popen("bin/pal -n -S  test/asc/arrays.pal", "r");
		ASSERT_NE(palout, (void*)0);

		int val;
		ASSERT_EQ(fscanf(palout, "%d", &val), 1);
		EXPECT_EQ(val, 11);
		ASSERT_EQ(fscanf(palout, "%d", &val), 1);
		EXPECT_EQ(val, 22);
		ASSERT_EQ(fscanf(palout, "%d", &val), 1);
		EXPECT_EQ(val, 33);
		ASSERT_EQ(fscanf(palout, "%d", &val), 1);
		EXPECT_EQ(val, 44);
		pclose(palout);
	}

	TEST(CodegenTest, TestArrayCharIndex)
	{
		ofstream testfile("test/asc/arraycharindex.pal");

		testfile << "program test(input, output);" << endl;
		testfile << "var" << endl;
		testfile << "	a : array['a'..'z'] of char;" << endl;
		testfile << "begin" << endl;
		testfile << "	a['w'] := 'q';" << endl;
		testfile << "	a['x'] := 'r';" << endl;
		testfile << "	write(a['w']);" << endl;
		testfile << "	write(a['x']);" << endl;
		testfile << "end." << endl;

		testfile.close();

		FILE* palout = popen("bin/pal -n -S  test/asc/arraycharindex.pal", "r");
		ASSERT_NE(palout, (void*)0);

		char val;
		ASSERT_EQ(fscanf(palout, "%c", &val), 1);
		EXPECT_EQ(val, 'q');
		ASSERT_EQ(fscanf(palout, "%c", &val), 1);
		EXPECT_EQ(val, 'r');
		pclose(palout);
	}

	TEST(CodegenTest, TestArrayCharIndex2)
	{
		ofstream testfile("test/asc/arraycharindex.pal");

		testfile << "program test(input, output);" << endl;
		testfile << "var" << endl;
		testfile << "	a : array['a'..'z'] of array['a'..'z'] of char;" << endl;
		testfile << "begin" << endl;
		testfile << "	a['w']['x'] := 'q';" << endl;
		testfile << "	a['w']['w'] := 'r';" << endl;
		testfile << "	a['x','x'] := 's';" << endl;
		testfile << "	a['x','w'] := 't';" << endl;
		testfile << "	write(a['w']['x']);" << endl;
		testfile << "	write(a['w']['w']);" << endl;
		testfile << "	write(a['x','x']);" << endl;
		testfile << "	write(a['x','w']);" << endl;
		testfile << "end." << endl;

		testfile.close();

		FILE* palout = popen("bin/pal -n -S  test/asc/arraycharindex.pal", "r");
		ASSERT_NE(palout, (void*)0);

		char val;
		ASSERT_EQ(fscanf(palout, "%c", &val), 1);
		EXPECT_EQ(val, 'q');
		ASSERT_EQ(fscanf(palout, "%c", &val), 1);
		EXPECT_EQ(val, 'r');
		ASSERT_EQ(fscanf(palout, "%c", &val), 1);
		EXPECT_EQ(val, 's');
		ASSERT_EQ(fscanf(palout, "%c", &val), 1);
		EXPECT_EQ(val, 't');
		pclose(palout);
	}

	TEST(CodegenTest, TestArrayEnumIndex)
	{
		ofstream testfile("test/asc/enumindex.pal");

		testfile << "program test(input, output);" << endl;
		testfile << "type" << endl;
		testfile << "	t = (hey, dude, whats, up);" << endl;
		testfile << "var" << endl;
		testfile << "	a : array[hey .. up] of integer;" << endl;
		testfile << "begin" << endl;
		testfile << "	a[hey] := 11;" << endl;
		testfile << "	a[dude] := 22;" << endl;
		testfile << "	a[whats] := 33;" << endl;
		testfile << "	a[up] := 44;" << endl;
		testfile << "	writeln(a[hey]);" << endl;
		testfile << "	writeln(a[dude]);" << endl;
		testfile << "	writeln(a[whats]);" << endl;
		testfile << "	writeln(a[up]);" << endl;
		testfile << "end." << endl;

		testfile.close();

		FILE* palout = popen("bin/pal -n -S  test/asc/enumindex.pal", "r");
		ASSERT_NE(palout, (void*)0);

		int val;
		ASSERT_EQ(fscanf(palout, "%d", &val), 1);
		EXPECT_EQ(val, 11);
		ASSERT_EQ(fscanf(palout, "%d", &val), 1);
		EXPECT_EQ(val, 22);
		ASSERT_EQ(fscanf(palout, "%d", &val), 1);
		EXPECT_EQ(val, 33);
		ASSERT_EQ(fscanf(palout, "%d", &val), 1);
		EXPECT_EQ(val, 44);
		pclose(palout);
	}

	TEST(CodegenTest, TestArrayEnumIndex2)
	{
		ofstream testfile("test/asc/enumindex.pal");

		testfile << "program test(input, output);" << endl;
		testfile << "type" << endl;
		testfile << "	t = (hey, dude, whats, up);" << endl;
		testfile << "var" << endl;
		testfile << "	a : array[t] of integer;" << endl;
		testfile << "begin" << endl;
		testfile << "	a[hey] := 11;" << endl;
		testfile << "	a[dude] := 22;" << endl;
		testfile << "	a[whats] := 33;" << endl;
		testfile << "	a[up] := 44;" << endl;
		testfile << "	writeln(a[hey]);" << endl;
		testfile << "	writeln(a[dude]);" << endl;
		testfile << "	writeln(a[whats]);" << endl;
		testfile << "	writeln(a[up]);" << endl;
		testfile << "end." << endl;

		testfile.close();

		FILE* palout = popen("bin/pal -n -S  test/asc/enumindex.pal", "r");
		ASSERT_NE(palout, (void*)0);

		int val;
		ASSERT_EQ(fscanf(palout, "%d", &val), 1);
		EXPECT_EQ(val, 11);
		ASSERT_EQ(fscanf(palout, "%d", &val), 1);
		EXPECT_EQ(val, 22);
		ASSERT_EQ(fscanf(palout, "%d", &val), 1);
		EXPECT_EQ(val, 33);
		ASSERT_EQ(fscanf(palout, "%d", &val), 1);
		EXPECT_EQ(val, 44);
		pclose(palout);
	}

	TEST(CodegenTest, TestArrayBoolIndex)
	{
		ofstream testfile("test/asc/boolindex.pal");

		testfile << "program test(input, output);" << endl;
		testfile << "var" << endl;
		testfile << "	a : array[boolean] of integer;" << endl;
		testfile << "begin" << endl;
		testfile << "	a[false] := 11;" << endl;
		testfile << "	a[true] := 22;" << endl;
		testfile << "	writeln(a[false]);" << endl;
		testfile << "	writeln(a[true]);" << endl;
		testfile << "end." << endl;

		testfile.close();

		FILE* palout = popen("bin/pal -n -S  test/asc/boolindex.pal", "r");
		ASSERT_NE(palout, (void*)0);

		int val;
		ASSERT_EQ(fscanf(palout, "%d", &val), 1);
		EXPECT_EQ(val, 11);
		ASSERT_EQ(fscanf(palout, "%d", &val), 1);
		EXPECT_EQ(val, 22);
		pclose(palout);
	}

	/* This is semantically correct, but.... 16 GB array.. ehhh... 
	TEST(CodegenTest, TestArrayTypeIndex)
	{
		ofstream testfile("test/asc/typeIndexInt.pal");

		testfile << "program test(input, output);" << endl;
		testfile << "var" << endl;
		testfile << "	a : array[integer] of integer;" << endl;
		testfile << "begin" << endl;
		testfile << "	a[100] := 11;" << endl;
		testfile << "	a[101] := 22;" << endl;
		testfile << "	writeln(a[100]);" << endl;
		testfile << "	writeln(a[101]);" << endl;
		testfile << "end." << endl;

		testfile.close();

		FILE* palout = popen("bin/pal -n -S  test/asc/typeIndexInt.pal", "r");
		ASSERT_NE(palout, (void*)0);

		int val;
		ASSERT_EQ(fscanf(palout, "%d", &val), 1);
		EXPECT_EQ(val, 11);
		ASSERT_EQ(fscanf(palout, "%d", &val), 1);
		EXPECT_EQ(val, 22);
		pclose(palout);
	}
	*/

	TEST(CodegenTest, TestArrayTypeIndex2)
	{
		ofstream testfile("test/asc/typeIndex.pal");

		testfile << "program test(input, output);" << endl;
		testfile << "var" << endl;
		testfile << "	a : array[char] of integer;" << endl;
		testfile << "begin" << endl;
		testfile << "	a['b'] := 11;" << endl;
		testfile << "	a['c'] := 22;" << endl;
		testfile << "	writeln(a['b']);" << endl;
		testfile << "	writeln(a['c']);" << endl;
		testfile << "end." << endl;

		testfile.close();

		FILE* palout = popen("bin/pal -n -S  test/asc/typeIndex.pal", "r");
		ASSERT_NE(palout, (void*)0);

		int val;
		ASSERT_EQ(fscanf(palout, "%d", &val), 1);
		EXPECT_EQ(val, 11);
		ASSERT_EQ(fscanf(palout, "%d", &val), 1);
		EXPECT_EQ(val, 22);
		pclose(palout);
	}

	TEST(CodegenTest, TestArrayCopy)
	{
		ofstream testfile("test/asc/arraycopy.pal");

		testfile << "program test(input, output);" << endl;
		testfile << "var" << endl;
		testfile << "	a, b : array[1 .. 4] of integer;" << endl;
		testfile << "begin" << endl;
		testfile << "	a[1] := 11;" << endl;
		testfile << "	a[2] := 22;" << endl;
		testfile << "	a[3] := 33;" << endl;
		testfile << "	a[4] := 44;" << endl;
		testfile << "	b := a;" << endl;
		testfile << "	writeln(b[1]);" << endl;
		testfile << "	writeln(b[2]);" << endl;
		testfile << "	writeln(b[3]);" << endl;
		testfile << "	writeln(b[4]);" << endl;
		testfile << "end." << endl;

		testfile.close();

		FILE* palout = popen("bin/pal -n -S  test/asc/arraycopy.pal", "r");
		ASSERT_NE(palout, (void*)0);

		int val;
		ASSERT_EQ(fscanf(palout, "%d", &val), 1);
		EXPECT_EQ(val, 11);
		ASSERT_EQ(fscanf(palout, "%d", &val), 1);
		EXPECT_EQ(val, 22);
		ASSERT_EQ(fscanf(palout, "%d", &val), 1);
		EXPECT_EQ(val, 33);
		ASSERT_EQ(fscanf(palout, "%d", &val), 1);
		EXPECT_EQ(val, 44);
		pclose(palout);
	}

	TEST(CodegenTest, TestRead)
	{
		ofstream testfile("test/asc/read.pal");

		testfile << "program test(input, output);" << endl;
		testfile << "var" << endl;
		testfile << "	a, b : integer;" << endl;
		testfile << "begin" << endl;
		testfile << "	read(a);" << endl;
		testfile << "	read(b);" << endl;
		testfile << "	writeln(a);" << endl;
		testfile << "	writeln(b);" << endl;
		testfile << "	writeln(a + b);" << endl;
		testfile << "end." << endl;

		testfile.close();

		ofstream input("test/asc/read.in");
		input << "2 3" << endl;
		input.close();

		FILE* palout = popen("bin/pal -n -S  test/asc/read.pal < test/asc/read.in", "r");
		ASSERT_NE(palout, (void*)0);

		int val;
		ASSERT_EQ(fscanf(palout, "%d", &val), 1);
		EXPECT_EQ(val, 2);
		ASSERT_EQ(fscanf(palout, "%d", &val), 1);
		EXPECT_EQ(val, 3);
		ASSERT_EQ(fscanf(palout, "%d", &val), 1);
		EXPECT_EQ(val, 5);
		pclose(palout);
	}

	TEST(CodegenTest, TestReadln)
	{
		ofstream testfile("test/asc/read.pal");

		testfile << "program test(input, output);" << endl;
		testfile << "var" << endl;
		testfile << "	a, b : integer;" << endl;
		testfile << "begin" << endl;
		testfile << "	readln(a);" << endl;
		testfile << "	readln(b);" << endl;
		testfile << "	writeln(a);" << endl;
		testfile << "	writeln(b);" << endl;
		testfile << "	writeln(a + b);" << endl;
		testfile << "end." << endl;

		testfile.close();

		ofstream input("test/asc/read.in");
		input << "2" << endl;
		input << "3" << endl;
		input.close();

		FILE* palout = popen("bin/pal -n -S  test/asc/read.pal < test/asc/read.in", "r");
		ASSERT_NE(palout, (void*)0);

		int val;
		ASSERT_EQ(fscanf(palout, "%d", &val), 1);
		EXPECT_EQ(val, 2);
		ASSERT_EQ(fscanf(palout, "%d", &val), 1);
		EXPECT_EQ(val, 3);
		ASSERT_EQ(fscanf(palout, "%d", &val), 1);
		EXPECT_EQ(val, 5);
		pclose(palout);
	}

	TEST(CodegenTest, TestReadChar)
	{
		ofstream testfile("test/asc/read.pal");

		testfile << "program test(input, output);" << endl;
		testfile << "var" << endl;
		testfile << "	a, b : char;" << endl;
		testfile << "begin" << endl;
		testfile << "	read(a);" << endl;
		testfile << "	read(b);" << endl;
		testfile << "	write(a);" << endl;
		testfile << "	write(b);" << endl;
		testfile << "end." << endl;

		testfile.close();

		ofstream input("test/asc/read.in");
		input << "xy" << endl;
		input.close();

		FILE* palout = popen("bin/pal -n -S  test/asc/read.pal < test/asc/read.in", "r");
		ASSERT_NE(palout, (void*)0);

		char val;
		ASSERT_EQ(fscanf(palout, "%c", &val), 1);
		EXPECT_EQ(val, 'x');
		ASSERT_EQ(fscanf(palout, "%c", &val), 1);
		EXPECT_EQ(val, 'y');
		pclose(palout);
	}

	TEST(CodegenTest, TestReadReal)
	{
		ofstream testfile("test/asc/read.pal");

		testfile << "program test(input, output);" << endl;
		testfile << "var" << endl;
		testfile << "	a, b : real;" << endl;
		testfile << "begin" << endl;
		testfile << "	read(a);" << endl;
		testfile << "	read(b);" << endl;
		testfile << "	writeln(a);" << endl;
		testfile << "	writeln(b);" << endl;
		testfile << "end." << endl;

		testfile.close();

		ofstream input("test/asc/read.in");
		input << "3.14 2.73" << endl;
		input.close();

		FILE* palout = popen("bin/pal -n -S  test/asc/read.pal < test/asc/read.in", "r");
		ASSERT_NE(palout, (void*)0);

		float val;
		ASSERT_EQ(fscanf(palout, "%f", &val), 1);
		EXPECT_FLOAT_EQ(val, 3.14);
		ASSERT_EQ(fscanf(palout, "%f", &val), 1);
		EXPECT_FLOAT_EQ(val, 2.73);
		pclose(palout);
	}
}

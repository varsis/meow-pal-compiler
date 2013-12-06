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
	
	TEST(CodegenTest, SquareRootTest)
	{
		ofstream testfile("test/asc/test.pal");
		
		testfile << "program test(input, output);" << endl;
		testfile << "const" << endl;
		testfile << "\tx = 9;" << endl;
		testfile << "begin" << endl;
		testfile << "   sqrt(x);" << endl;
		testfile << "end." << endl;
		
		testfile.close();
		
		FILE* palout = popen("bin/pal -S -n test/asc/test.pal", "r");
		ASSERT_NE(palout, (void*)0);
		
		double i;
		
		ASSERT_EQ(fscanf(palout, "%f", &i), 1);
		EXPECT_FLOAT_EQ(i, 3.0);
		
		pclose(palout);
	}
	
	TEST(CodegenTest, SquareRootTest2)
	{
		ofstream testfile("test/asc/test.pal");
		
		testfile << "program test(input, output);" << endl;
		testfile << "const" << endl;
		testfile << "\tx = 9;" << endl;
		testfile << "begin" << endl;
		testfile << "   sqrt(x);" << endl;
		testfile << "end." << endl;
		
		testfile.close();
		
		FILE* palout = popen("bin/pal -S -n test/asc/test.pal", "r");
		ASSERT_NE(palout, (void*)0);
		
		double i;
		
		ASSERT_EQ(fscanf(palout, "%f", &i), 1);
		EXPECT_FLOAT_EQ(i, 3.0);
		
		pclose(palout);
	}
	
	TEST(CodegenTest, lnFunctionTest)
	{
		ofstream testfile("test/asc/test.pal");
		
		testfile << "program test(input, output);" << endl;
		testfile << "var" << endl;
		testfile << "\ti : real;" << endl;
		testfile << "begin" << endl;
		testfile << "\ti:= 0.01;" << endl;
		testfile << "\twriteln(ln(i));" << endl;
		testfile << "end." << endl;
		
		testfile.close();
		
		FILE* palout = popen("bin/pal -S -n test/asc/test.pal", "r");
		ASSERT_NE(palout, (void*)0);
		
		double i;
		
		ASSERT_EQ(fscanf(palout, "%d", &i), 1);
		EXPECT_FLOAT_EQ(i, 3.0);
		
		pclose(palout);
	}
	
	TEST(CodegenTest, TestAndLogical)
	{
		ofstream testfile("test/asc/testLogicalAnd.pal");
		
		testfile << "program test(input, output);" << endl;
		testfile << "const" << endl;
		testfile << "\tcorrectString = 'a and B';" << endl;
		testfile << "var" << endl;
		testfile << "\ta : boolean;" << endl;
		testfile << "\tb : boolean;" << endl;
		testfile << "begin" << endl;
		testfile << "a := true;" << endl;
		testfile << "b := true;" << endl;
		testfile << "	if (a and b) then" << endl;
		testfile << "		writeln('a and b')" << endl;
		testfile << "end." << endl;
		
		testfile.close();
		
		FILE* palout = popen("bin/pal -n test/asc/testLogicalAnd.pal", "r");
		ASSERT_NE(palout, (void*)0);
		
		char str [300];
		fgets(str, 300 , palout);
		EXPECT_STRCASEEQ(str, "a and B\n");

		
		pclose(palout);
	}
	
	TEST(CodegenTest, TestAndLogical2)
	{
		ofstream testfile("test/asc/testLogicalAnd.pal");
		
		testfile << "program test(input, output);" << endl;
		testfile << "const" << endl;
		testfile << "\tcorrectString = 'a and B';" << endl;
		testfile << "var" << endl;
		testfile << "\ta : boolean;" << endl;
		testfile << "\tb : boolean;" << endl;
		testfile << "begin" << endl;
		testfile << "a := true;" << endl;
		testfile << "b := false;" << endl;
		testfile << "	if (not(a and b)) then" << endl;
		testfile << "		writeln('a and b')" << endl;
		testfile << "end." << endl;
		
		testfile.close();
		
		FILE* palout = popen("bin/pal -n test/asc/testLogicalAnd.pal", "r");
		ASSERT_NE(palout, (void*)0);
		
		char str [300];
		fgets(str, 300 , palout);
		EXPECT_STRCASEEQ(str, "a and B\n");
		
		
		pclose(palout);
	}
	
	TEST(CodegenTest, TestAndLogical3)
	{
		ofstream testfile("test/asc/testLogicalAnd.pal");
		
		testfile << "program test(input, output);" << endl;
		testfile << "const" << endl;
		testfile << "\tcorrectString = 'a and B';" << endl;
		testfile << "var" << endl;
		testfile << "\ta : boolean;" << endl;
		testfile << "\tb : boolean;" << endl;
		testfile << "begin" << endl;
		testfile << "a := false;" << endl;
		testfile << "b := false;" << endl;
		testfile << "	if (a and b) then" << endl;
		testfile << "		writeln('a and b')" << endl;
		testfile << " else" << endl;
		testfile << "		writeln('a and b false')" << endl;
		testfile << "end." << endl;
		
		testfile.close();
		
		FILE* palout = popen("bin/pal -n test/asc/testLogicalAnd.pal", "r");
		ASSERT_NE(palout, (void*)0);
		
		char str [300];
		fgets(str, 300 , palout);
		EXPECT_STRCASEEQ(str, "a and B false\n");
		
		
		pclose(palout);
	}
	
	TEST(CodegenTest, TestAndLogical4)
	{
		ofstream testfile("test/asc/testLogicalAnd4.pal");
		
		testfile << "program test(input, output);" << endl;
		testfile << "var" << endl;
		testfile << "\ta : boolean;" << endl;
		testfile << "\tb : boolean;" << endl;
		testfile << "\tc : boolean;" << endl;
		testfile << "begin" << endl;
		testfile << "a := true;" << endl;
		testfile << "b := true;" << endl;
		testfile << "c := true;" << endl;
		testfile << "	if ((a and b) and c) then" << endl;
		testfile << "		writeln('a and b and c')" << endl;
		testfile << " else" << endl;
		testfile << "		writeln('a and b and c false')" << endl;
		testfile << "end." << endl;
		
		testfile.close();
		
		FILE* palout = popen("bin/pal -n test/asc/testLogicalAnd4.pal", "r");
		ASSERT_NE(palout, (void*)0);
		
		char str [300];
		fgets(str, 300 , palout);
		EXPECT_STRCASEEQ(str, "a and b and c\n");
		
		
		pclose(palout);
	}
	
	TEST(CodegenTest, TestOrLogical)
	{
		ofstream testfile("test/asc/testLogicalAnd.pal");
		
		testfile << "program test(input, output);" << endl;
		testfile << "var" << endl;
		testfile << "\ta : boolean;" << endl;
		testfile << "\tb : boolean;" << endl;
		testfile << "\tc : boolean;" << endl;
		testfile << "begin" << endl;
		testfile << "a := true;" << endl;
		testfile << "b := false;" << endl;
		testfile << "c := true;" << endl;
		testfile << "	if (a or b) then" << endl;
		testfile << "		writeln('a or b')" << endl;
		testfile << " else" << endl;
		testfile << "		writeln('a or b false')" << endl;
		testfile << "end." << endl;
		
		testfile.close();
		
		FILE* palout = popen("bin/pal -n test/asc/testLogicalAnd.pal", "r");
		ASSERT_NE(palout, (void*)0);
		
		char str [300];
		fgets(str, 300 , palout);
		EXPECT_STRCASEEQ(str, "a or b\n");
		
		
		pclose(palout);
	}
	
	TEST(CodegenTest, TestOrLogical2)
	{
		ofstream testfile("test/asc/testLogicalAnd.pal");
		
		testfile << "program test(input, output);" << endl;
		testfile << "var" << endl;
		testfile << "\ta : boolean;" << endl;
		testfile << "\tb : boolean;" << endl;
		testfile << "\tc : boolean;" << endl;
		testfile << "begin" << endl;
		testfile << "a := false;" << endl;
		testfile << "b := true;" << endl;
		testfile << "c := true;" << endl;
		testfile << "	if (a or b) then" << endl;
		testfile << "		writeln('a or b')" << endl;
		testfile << " else" << endl;
		testfile << "		writeln('a or b false')" << endl;
		testfile << "end." << endl;
		
		testfile.close();
		
		FILE* palout = popen("bin/pal -n test/asc/testLogicalAnd.pal", "r");
		ASSERT_NE(palout, (void*)0);
		
		char str [300];
		fgets(str, 300 , palout);
		EXPECT_STRCASEEQ(str, "a or b\n");
		
		
		pclose(palout);
	}
	
	
	TEST(CodegenTest, TestOrLogical3)
	{
		ofstream testfile("test/asc/testLogicalAnd.pal");
		
		testfile << "program test(input, output);" << endl;
		testfile << "var" << endl;
		testfile << "\ta : boolean;" << endl;
		testfile << "\tb : boolean;" << endl;
		testfile << "\tc : boolean;" << endl;
		testfile << "begin" << endl;
		testfile << "a := false;" << endl;
		testfile << "b := false;" << endl;
		testfile << "c := true;" << endl;
		testfile << "	if (a or b) then" << endl;
		testfile << "		writeln('a or b')" << endl;
		testfile << " else" << endl;
		testfile << "		writeln('a or b false')" << endl;
		testfile << "end." << endl;
		
		testfile.close();
		
		FILE* palout = popen("bin/pal -n test/asc/testLogicalAnd.pal", "r");
		ASSERT_NE(palout, (void*)0);
		
		char str [300];
		fgets(str, 300 , palout);
		EXPECT_STRCASEEQ(str, "a or b false\n");
		
		
		pclose(palout);
	}
	
	TEST(CodegenTest, TestOrLogical4)
	{
		ofstream testfile("test/asc/testLogicalAnd.pal");
		
		testfile << "program test(input, output);" << endl;
		testfile << "var" << endl;
		testfile << "\ta : boolean;" << endl;
		testfile << "\tb : boolean;" << endl;
		testfile << "\tc : boolean;" << endl;
		testfile << "begin" << endl;
		testfile << "a := false;" << endl;
		testfile << "b := false;" << endl;
		testfile << "c := true;" << endl;
		testfile << "	if (a or b or c) then" << endl;
		testfile << "		writeln('a or b or c')" << endl;
		testfile << " else" << endl;
		testfile << "		writeln('a or b false')" << endl;
		testfile << "end." << endl;
		
		testfile.close();
		
		FILE* palout = popen("bin/pal -n test/asc/testLogicalAnd.pal", "r");
		ASSERT_NE(palout, (void*)0);
		
		char str [300];
		fgets(str, 300 , palout);
		EXPECT_STRCASEEQ(str, "a or b or c\n");
		
		
		pclose(palout);
	}
	
	TEST(CodegenTest, TestOrAndLogical)
	{
		ofstream testfile("test/asc/testLogicalAnd.pal");
		
		testfile << "program test(input, output);" << endl;
		testfile << "var" << endl;
		testfile << "\ta : boolean;" << endl;
		testfile << "\tb : boolean;" << endl;
		testfile << "\tc : boolean;" << endl;
		testfile << "begin" << endl;
		testfile << "a := false;" << endl;
		testfile << "b := true;" << endl;
		testfile << "c := true;" << endl;
		testfile << "	if (a or b and c) then" << endl;
		testfile << "		writeln('a or b and c')" << endl;
		testfile << " else" << endl;
		testfile << "		writeln('a or b false')" << endl;
		testfile << "end." << endl;
		
		testfile.close();
		
		FILE* palout = popen("bin/pal -n test/asc/testLogicalAnd.pal", "r");
		ASSERT_NE(palout, (void*)0);
		
		char str [300];
		fgets(str, 300 , palout);
		EXPECT_STRCASEEQ(str, "a or b and c\n");
		
		
		pclose(palout);
	}
	
	TEST(CodegenTest, TestOrAndLogical2)
	{
		ofstream testfile("test/asc/testLogicalAnd.pal");
		
		testfile << "program test(input, output);" << endl;
		testfile << "var" << endl;
		testfile << "\ta : boolean;" << endl;
		testfile << "\tb : boolean;" << endl;
		testfile << "\tc : boolean;" << endl;
		testfile << "begin" << endl;
		testfile << "a := false;" << endl;
		testfile << "b := false;" << endl;
		testfile << "c := false;" << endl;
		testfile << "	if (a or b and c) then" << endl;
		testfile << "		writeln('a or b and c')" << endl;
		testfile << " else" << endl;
		testfile << "		writeln('a or b and c false')" << endl;
		testfile << "end." << endl;
		
		testfile.close();
		
		FILE* palout = popen("bin/pal -n test/asc/testLogicalAnd.pal", "r");
		ASSERT_NE(palout, (void*)0);
		
		char str [300];
		fgets(str, 300 , palout);
		EXPECT_STRCASEEQ(str, "a or b and c false\n");
		
		
		pclose(palout);
	}
	
	TEST(CodegenTest, TestOrAndNotLogical)
	{
		ofstream testfile("test/asc/testLogicalAnd.pal");
		
		testfile << "program test(input, output);" << endl;
		testfile << "var" << endl;
		testfile << "\ta : boolean;" << endl;
		testfile << "\tb : boolean;" << endl;
		testfile << "\tc : boolean;" << endl;
		testfile << "begin" << endl;
		testfile << "a := false;" << endl;
		testfile << "b := false;" << endl;
		testfile << "c := false;" << endl;
		testfile << "	if (not(a or b and c)) then" << endl;
		testfile << "		writeln('not(a or b and c)')" << endl;
		testfile << " else" << endl;
		testfile << "		writeln('a or b and c false')" << endl;
		testfile << "end." << endl;
		
		testfile.close();
		
		FILE* palout = popen("bin/pal -n test/asc/testLogicalAnd.pal", "r");
		ASSERT_NE(palout, (void*)0);
		
		char str [300];
		fgets(str, 300 , palout);
		EXPECT_STRCASEEQ(str, "not(a or b and c)\n");
		
		
		pclose(palout);
	}
	
	TEST(CodegenTest, TestNotLogical)
	{
		ofstream testfile("test/asc/testLogicalAnd.pal");
		
		testfile << "program test(input, output);" << endl;
		testfile << "var" << endl;
		testfile << "\ta : boolean;" << endl;
		testfile << "\tb : boolean;" << endl;
		testfile << "\tc : boolean;" << endl;
		testfile << "begin" << endl;
		testfile << "a := false;" << endl;
		testfile << "b := false;" << endl;
		testfile << "c := false;" << endl;
		testfile << "	if (not a) then" << endl;
		testfile << "		writeln('not a')" << endl;
		testfile << " else" << endl;
		testfile << "		writeln('a or b and c false')" << endl;
		testfile << "end." << endl;
		
		testfile.close();
		
		FILE* palout = popen("bin/pal -n test/asc/testLogicalAnd.pal", "r");
		ASSERT_NE(palout, (void*)0);
		
		char str [300];
		fgets(str, 300 , palout);
		EXPECT_STRCASEEQ(str, "not a\n");
		
		
		pclose(palout);
	}
	
	TEST(CodegenTest, TestNotLogical2)
	{
		ofstream testfile("test/asc/testLogicalAnd.pal");
		
		testfile << "program test(input, output);" << endl;
		testfile << "var" << endl;
		testfile << "\ta : boolean;" << endl;
		testfile << "\tb : boolean;" << endl;
		testfile << "\tc : boolean;" << endl;
		testfile << "begin" << endl;
		testfile << "a := true;" << endl;
		testfile << "b := false;" << endl;
		testfile << "c := false;" << endl;
		testfile << "	if (not a) then" << endl;
		testfile << "		writeln('not a')" << endl;
		testfile << " else" << endl;
		testfile << "		writeln('a')" << endl;
		testfile << "end." << endl;
		
		testfile.close();
		
		FILE* palout = popen("bin/pal -n test/asc/testLogicalAnd.pal", "r");
		ASSERT_NE(palout, (void*)0);
		
		char str [300];
		fgets(str, 300 , palout);
		EXPECT_STRCASEEQ(str, "a\n");
		
		
		pclose(palout);
	}
	
	TEST(CodegenTest, TestAndLogical5)
	{
		ofstream testfile("test/asc/testLogicalAnd.pal");
		
		testfile << "program test(input, output);" << endl;
		testfile << "var" << endl;
		testfile << "\ta,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p : boolean;" << endl;
		testfile << "begin" << endl;
		testfile << "a := true;" << endl;
		testfile << "b := true;" << endl;
		testfile << "c := true;" << endl;
		testfile << "d := true;" << endl;
		testfile << "e := true;" << endl;
		testfile << "f := true;" << endl;
		testfile << "g := true;" << endl;
		testfile << "h := true;" << endl;
		testfile << "i := true;" << endl;
		testfile << "j := true;" << endl;
		testfile << "k := true;" << endl;
		testfile << "l := true;" << endl;
		testfile << "m := true;" << endl;
		testfile << "n := true;" << endl;
		testfile << "o := true;" << endl;
		testfile << "p := true;" << endl;
		testfile << "	if (a and b and c and d and e and f and g) then" << endl;
		testfile << "		writeln('all true')" << endl;
		testfile << " else" << endl;
		testfile << "		writeln('a')" << endl;
		testfile << "end." << endl;
		
		testfile.close();
		
		FILE* palout = popen("bin/pal -n test/asc/testLogicalAnd.pal", "r");
		ASSERT_NE(palout, (void*)0);
		
		char str [300];
		fgets(str, 300 , palout);
		EXPECT_STRCASEEQ(str, "all true\n");
		
		
		pclose(palout);
	}
	
	TEST(CodegenTest, TestLogical)
	{
		ofstream testfile("test/asc/testLogicalAnd.pal");
		
		testfile << "program test(input, output);" << endl;
		testfile << "var" << endl;
		testfile << "\ta,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p : boolean;" << endl;
		testfile << "begin" << endl;
		testfile << "a := true;" << endl;
		testfile << "b := false;" << endl;
		testfile << "c := true;" << endl;
		testfile << "d := true;" << endl;
		testfile << "e := true;" << endl;
		testfile << "f := true;" << endl;
		testfile << "g := true;" << endl;
		testfile << "h := true;" << endl;
		testfile << "i := true;" << endl;
		testfile << "j := true;" << endl;
		testfile << "k := true;" << endl;
		testfile << "l := true;" << endl;
		testfile << "m := true;" << endl;
		testfile << "n := true;" << endl;
		testfile << "o := true;" << endl;
		testfile << "p := true;" << endl;
		testfile << "	if (a and b or c and d and e and f and g) then" << endl;
		testfile << "		writeln('all true')" << endl;
		testfile << " else" << endl;
		testfile << "		writeln('a')" << endl;
		testfile << "end." << endl;
		
		testfile.close();
		
		FILE* palout = popen("bin/pal -n test/asc/testLogicalAnd.pal", "r");
		ASSERT_NE(palout, (void*)0);
		
		char str [300];
		fgets(str, 300 , palout);
		EXPECT_STRCASEEQ(str, "all true\n");
		
		
		pclose(palout);
	}
	
	
	TEST(CodegenTest, TestLogical2)
	{
		ofstream testfile("test/asc/testLogicalAnd.pal");
		
		testfile << "program test(input, output);" << endl;
		testfile << "var" << endl;
		testfile << "\ta,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p : boolean;" << endl;
		testfile << "begin" << endl;
		testfile << "a := true;" << endl;
		testfile << "b := false;" << endl;
		testfile << "c := true;" << endl;
		testfile << "d := true;" << endl;
		testfile << "e := true;" << endl;
		testfile << "f := false;" << endl;
		testfile << "g := true;" << endl;
		testfile << "h := true;" << endl;
		testfile << "i := true;" << endl;
		testfile << "j := true;" << endl;
		testfile << "k := true;" << endl;
		testfile << "l := true;" << endl;
		testfile << "m := true;" << endl;
		testfile << "n := true;" << endl;
		testfile << "o := true;" << endl;
		testfile << "p := true;" << endl;
		testfile << "	if (a and b or c and d and e and f and g) then" << endl;
		testfile << "		writeln('all true')" << endl;
		testfile << " else" << endl;
		testfile << "		writeln('not')" << endl;
		testfile << "end." << endl;
		
		testfile.close();
		
		FILE* palout = popen("bin/pal -n test/asc/testLogicalAnd.pal", "r");
		ASSERT_NE(palout, (void*)0);
		
		char str [300];
		fgets(str, 300 , palout);
		EXPECT_STRCASEEQ(str, "not\n");
		
		
		pclose(palout);
	}
	
	TEST(CodegenTest, TestLogical3)
	{
		ofstream testfile("test/asc/testLogicalAnd.pal");
		
		testfile << "program test(input, output);" << endl;
		testfile << "var" << endl;
		testfile << "\ta,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p : boolean;" << endl;
		testfile << "begin" << endl;
		testfile << "a := true;" << endl;
		testfile << "b := false;" << endl;
		testfile << "c := true;" << endl;
		testfile << "d := true;" << endl;
		testfile << "e := true;" << endl;
		testfile << "f := false;" << endl;
		testfile << "g := true;" << endl;
		testfile << "h := true;" << endl;
		testfile << "i := true;" << endl;
		testfile << "j := true;" << endl;
		testfile << "k := true;" << endl;
		testfile << "l := true;" << endl;
		testfile << "m := true;" << endl;
		testfile << "n := true;" << endl;
		testfile << "o := true;" << endl;
		testfile << "p := true;" << endl;
		testfile << "	if (not a and b or not c and d and not e and not f and g) then" << endl;
		testfile << "		writeln('all true')" << endl;
		testfile << " else" << endl;
		testfile << "		writeln('not')" << endl;
		testfile << "end." << endl;
		
		testfile.close();
		
		FILE* palout = popen("bin/pal -n test/asc/testLogicalAnd.pal", "r");
		ASSERT_NE(palout, (void*)0);
		
		char str [300];
		fgets(str, 300 , palout);
		EXPECT_STRCASEEQ(str, "not\n");
		
		
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

	TEST(CodegenTest, TestProcedure3)
	{
		ofstream testfile("test/asc/ptest3.pal");

		testfile << "program test(input, output);" << endl;
		testfile << "var a : integer;" << endl;
		testfile << "procedure foo(i : integer);" << endl;
		testfile << "begin" << endl;
		testfile << "  writeln(i);" << endl;
		testfile << "end;" << endl;
		testfile << "begin" << endl;
		testfile << "  a := 45;" << endl;
		testfile << "  foo(a-1);" << endl;
		testfile << "  foo(a+1);" << endl;
		testfile << "  foo(a*2);" << endl;
		testfile << "end." << endl;

		testfile.close();

		FILE* palout = popen("bin/pal -n -S  test/asc/ptest3.pal", "r");
		ASSERT_NE(palout, (void*)0);

		int val;
		ASSERT_EQ(fscanf(palout, "%d", &val), 1);
		EXPECT_EQ(val, 44);
		ASSERT_EQ(fscanf(palout, "%d", &val), 1);
		EXPECT_EQ(val, 46);
		ASSERT_EQ(fscanf(palout, "%d", &val), 1);
		EXPECT_EQ(val, 90);

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

	TEST(CodegenTest, TestReadln0)
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

	TEST(CodegenTest, TestReadln1)
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
		testfile << "	writeln(a*b);" << endl;
		testfile << "end." << endl;

		testfile.close();

		ofstream input("test/asc/read.in");
		input << "2 36 366 2 3 4 56 8 9 999 7 66 55 6 5555 444   " << endl;
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
		EXPECT_EQ(val, 6);
		pclose(palout);
	}

	TEST(CodegenTest, TestReadChar)
	{
		ofstream testfile("test/asc/readchar.pal");

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

		FILE* palout = popen("bin/pal -n -S  test/asc/readchar.pal < test/asc/read.in", "r");
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

	TEST(CodegenTest, TestArrayBoundCheck0)
	{
		ofstream testfile("test/asc/arraybound.pal");
		
		testfile << "program test(input, output);" << endl;
		testfile << "var" << endl;
		testfile << "	a : array[1..23] of integer;" << endl;
		testfile << "begin" << endl;
		testfile << "	a[100] := 90;" << endl;
		testfile << "end." << endl;

		testfile.close();

		FILE* palout = popen("bin/pal -n -S test/asc/arraybound.pal", "r");
		ASSERT_NE(palout, (void*)0);
		
		char array[256];

		ASSERT_EQ(fscanf(palout, "%s", array), 1);
		EXPECT_STREQ(array, "ERROR");
		pclose(palout);
	}

	TEST(CodegenTest, TestArrayBoundCheck1)
	{
		ofstream testfile("test/asc/arraybound.pal");
		
		testfile << "program test(input, output);" << endl;
		testfile << "var" << endl;
		testfile << "	a : array[1..23] of integer;" << endl;
		testfile << "begin" << endl;
		testfile << "	a[0] := 90;" << endl;
		testfile << "end." << endl;

		testfile.close();

		FILE* palout = popen("bin/pal -n -S test/asc/arraybound.pal", "r");
		ASSERT_NE(palout, (void*)0);
		
		char array[256];

		ASSERT_EQ(fscanf(palout, "%s", array), 1);
		EXPECT_STREQ(array, "ERROR");
		pclose(palout);
	}
	
	TEST(CodegenTest, TestArrayBoundCheck2)
	{
		ofstream testfile("test/asc/arraybound.pal");
		
		testfile << "program test(input, output);" << endl;
		testfile << "var" << endl;
		testfile << "	a : array['a'..'v'] of integer;" << endl;
		testfile << "begin" << endl;
		testfile << "	a['x'] := 90;" << endl;
		testfile << "end." << endl;

		testfile.close();

		FILE* palout = popen("bin/pal -n -S test/asc/arraybound.pal", "r");
		ASSERT_NE(palout, (void*)0);
		
		char array[256];

		ASSERT_EQ(fscanf(palout, "%s", array), 1);
		EXPECT_STREQ(array, "ERROR");
		pclose(palout);
	}
	
	TEST(CodegenTest, TestArrayBoundCheck3)
	{
		ofstream testfile("test/asc/arraybound.pal");
		
		testfile << "program test(input, output);" << endl;
		testfile << "type" << endl;
		testfile << "	b = (f,g,h,j);" << endl;
		testfile << "var" << endl;
		testfile << "	a : array[b] of integer;" << endl;
		testfile << "begin" << endl;
		testfile << "	a[g] := 90;" << endl;
		testfile << "	writeln(a[g]);" << endl;
		testfile << "end." << endl;

		testfile.close();

		FILE* palout = popen("bin/pal -n -S test/asc/arraybound.pal", "r");
		ASSERT_NE(palout, (void*)0);
		
		int value;

		ASSERT_EQ(fscanf(palout, "%d", &value), 1);
		EXPECT_EQ(value, 90);
		pclose(palout);
	}
	
	TEST(CodegenTest, TestExitContinue0)
	{
		ofstream testfile("test/asc/exitcontinue.pal");
		
		testfile << "program test(input, output);" << endl;
		testfile << "var" << endl;
		testfile << "	a : integer;" << endl;
		testfile << "begin" << endl;
		testfile << "	a := 0;" << endl;
		testfile << "	while(a <> 10) do" << endl;
		testfile << "	begin" << endl;
		testfile << "		a := a + 1;" << endl;
		testfile << "		continue;" << endl;
		testfile << "		writeln('a'); " << endl;
		testfile << "	end;" << endl;
		testfile << "writeln('b');" << endl;
		testfile << "end." << endl;

		testfile.close();

		FILE* palout = popen("bin/pal -n -S test/asc/exitcontinue.pal", "r");
		ASSERT_NE(palout, (void*)0);
		
		char b;

		ASSERT_EQ(fscanf(palout, "%c", &b), 1);
		EXPECT_EQ(b, 'b');
		pclose(palout);
	}
	
	TEST(CodegenTest, TestExitContinue1)
	{
		ofstream testfile("test/asc/exitcontinue.pal");
		
		testfile << "program test(input, output);" << endl;
		testfile << "var" << endl;
		testfile << "	a : integer;" << endl;
		testfile << "begin" << endl;
		testfile << "	a := 0;" << endl;
		testfile << "	while(a <> 10) do" << endl;
		testfile << "	begin" << endl;
		testfile << "		a := a + 1;" << endl;
		testfile << "		write('b');" << endl;
		testfile << "		exit;" << endl;
		testfile << "		writeln('a'); " << endl;
		testfile << "	end;" << endl;
		testfile << "end." << endl;

		testfile.close();

		FILE* palout = popen("bin/pal -n -S test/asc/exitcontinue.pal", "r");
		ASSERT_NE(palout, (void*)0);
		
		char b;

		ASSERT_EQ(fscanf(palout, "%c", &b), 1);
		EXPECT_EQ(b, 'b');
		ASSERT_NE(fscanf(palout, "%c", &b), 1);
		pclose(palout);
	}
	
	TEST(CodegenTest, TestRecursiveFunction0)
	{
		ofstream testfile("test/asc/recursive.pal");
		
		testfile << "program test(input, output);" << endl;
		testfile << "procedure b(a : integer);" << endl;
		testfile << "	begin" << endl;
		testfile << "		if (a <> 0) then" << endl;
		testfile << "		begin" << endl;
		testfile << "			write('a');" << endl;
		testfile << "			b(a - 1);" << endl;
		testfile << "		end;" << endl;
		testfile << "	end;" << endl;
		testfile << "begin" << endl;
		testfile << "	b(4);" << endl;
		testfile << "end." << endl;

		testfile.close();

		FILE* palout = popen("bin/pal -n -S test/asc/recursive.pal", "r");
		ASSERT_NE(palout, (void*)0);
		
		char b;

		ASSERT_EQ(fscanf(palout, "%c", &b), 1);
		EXPECT_EQ(b, 'a');
		ASSERT_EQ(fscanf(palout, "%c", &b), 1);
		EXPECT_EQ(b, 'a');
		ASSERT_EQ(fscanf(palout, "%c", &b), 1);
		EXPECT_EQ(b, 'a');
		ASSERT_EQ(fscanf(palout, "%c", &b), 1);
		EXPECT_EQ(b, 'a');

		ASSERT_EQ(fscanf(palout, "%c", &b), -1);

		pclose(palout);
	}

	TEST(CodegenTest, TestRecursiveFunction1)
	{
		ofstream testfile("test/asc/factorial.pal");
		
		testfile << "program test(input, output);" << endl;
		testfile << "function factorial(a : integer) : integer;" << endl;
		testfile << "begin" << endl;
		testfile << "  if (a <> 1) then" << endl;
		testfile << "    factorial := factorial(a - 1) * a;" << endl;
		testfile << "end;" << endl;
		testfile << "begin" << endl;
		testfile << "	writeln(factorial(4));" << endl;
		testfile << "	writeln(factorial(5));" << endl;
		testfile << "	writeln(factorial(6));" << endl;
		testfile << "	writeln(factorial(7));" << endl;
		testfile << "end." << endl;

		testfile.close();

		FILE* palout = popen("bin/pal -n -S test/asc/factorial.pal", "r");
		ASSERT_NE(palout, (void*)0);
		
		int a;

		ASSERT_EQ(fscanf(palout, "%d", &a), 1);
		EXPECT_EQ(a, 24);
		ASSERT_EQ(fscanf(palout, "%d", &a), 1);
		EXPECT_EQ(a, 120);
		ASSERT_EQ(fscanf(palout, "%d", &a), 1);
		EXPECT_EQ(a, 720);
		ASSERT_EQ(fscanf(palout, "%d", &a), 1);
		EXPECT_EQ(a, 5040);

		pclose(palout);
	}

	TEST(CodegenTest, TestReadString)
	{
		ofstream testfile("test/asc/read.pal");

		testfile << "program test(input, output);" << endl;
		testfile << "var" << endl;
		testfile << "	s : string;" << endl;
		testfile << "begin" << endl;
		testfile << "	readln(s);" << endl;
		testfile << "	writeln(s);" << endl;
		testfile << "	readln(s);" << endl;
		testfile << "	writeln(s);" << endl;
		testfile << "end." << endl;

		testfile.close();

		ofstream input("test/asc/read.in");
		input << "hello world!" << endl;
		input << "how is your day?" << endl;
		input.close();

		FILE* palout = popen("bin/pal -n -S  test/asc/read.pal < test/asc/read.in", "r");
		ASSERT_NE(palout, (void*)0);

		char* buf = new char[256];
		size_t bufsize = 255;

		ASSERT_GT(getline(&buf, &bufsize, palout), 0);
		EXPECT_EQ(string(buf), "hello world!\n"); 

		ASSERT_GT(getline(&buf, &bufsize, palout), 0);
		EXPECT_EQ(string(buf), "how is your day?\n"); 

		delete [] buf;

		pclose(palout);
	}
	
	TEST(CodegenTest, TestAssignString1)
	{
		ofstream testfile("test/asc/string.pal");

		testfile << "program test(input, output);" << endl;
		testfile << "var" << endl;
		testfile << "	s : array[1..4] of char;" << endl;
		testfile << "begin" << endl;
		testfile << "	s := 'word';" << endl;
		testfile << "	writeln(s);" << endl;
		testfile << "end." << endl;

		testfile.close();

		FILE* palout = popen("bin/pal -n -S  test/asc/string.pal", "r");
		ASSERT_NE(palout, (void*)0);

		char* buf = new char[256];
		size_t bufsize = 255;

		ASSERT_GT(getline(&buf, &bufsize, palout), 0);
		EXPECT_EQ(string(buf), "word\n"); 

		delete [] buf;

		pclose(palout);
	}

	TEST(CodegenTest, TestAssignString2)
	{
		ofstream testfile("test/asc/string.pal");

		testfile << "program test(input, output);" << endl;
		testfile << "var" << endl;
		testfile << "	s : string;" << endl;
		testfile << "begin" << endl;
		testfile << "	s := 'what is the meaning of life?';" << endl;
		testfile << "	writeln(s);" << endl;
		testfile << "	s := 'arf arf arf';" << endl;
		testfile << "	writeln(s);" << endl;
		testfile << "end." << endl;

		testfile.close();

		FILE* palout = popen("bin/pal -n -S  test/asc/string.pal", "r");
		ASSERT_NE(palout, (void*)0);

		char* buf = new char[256];
		size_t bufsize = 255;

		ASSERT_GT(getline(&buf, &bufsize, palout), 0);
		EXPECT_EQ(string(buf), "what is the meaning of life?\n"); 

		ASSERT_GT(getline(&buf, &bufsize, palout), 0);
		EXPECT_EQ(string(buf), "arf arf arf\n"); 

		delete [] buf;

		pclose(palout);
	}

	TEST(CodegenTest, TestAssignString3)
	{
		ofstream testfile("test/asc/string.pal");

		testfile << "program test(input, output);" << endl;
		testfile << "var" << endl;
		testfile << "	s : array[1..4] of char;" << endl;
		testfile << "begin" << endl;
		testfile << "	s := 'wordplussomemorestuff';" << endl;
		testfile << "	writeln(s);" << endl;
		testfile << "end." << endl;

		testfile.close();

		FILE* palout = popen("bin/pal -n -S  test/asc/string.pal", "r");
		ASSERT_NE(palout, (void*)0);

		char* buf = new char[256];
		size_t bufsize = 255;

		// string literal should get truncated to fit!

		ASSERT_GT(getline(&buf, &bufsize, palout), 0);
		EXPECT_EQ(string(buf), "word\n"); 

		delete [] buf;

		pclose(palout);
	}

	TEST(CodegenTest, TestPredefConsts)
	{
		ofstream testfile("test/asc/test.pal");

		testfile << "program test(input, output);" << endl;
		testfile << "begin" << endl;
		testfile << "   if (true) then" << endl;
		testfile << "		writeln(40);" << endl;
		testfile << "   if (false) then" << endl;
		testfile << "		writeln(50);" << endl;
		testfile << "	writeln(maxint);" << endl;
		testfile << "	writeln(minint);" << endl;
		testfile << "end." << endl;

		testfile.close();

		FILE* palout = popen("bin/pal -n test/asc/test.pal", "r");
		ASSERT_NE(palout, (void*)0);

		int i;

		ASSERT_EQ(fscanf(palout, "%d", &i), 1);
		EXPECT_EQ(i, 40);

		ASSERT_EQ(fscanf(palout, "%d", &i), 1);
		EXPECT_EQ(i, 2147483647);

		ASSERT_EQ(fscanf(palout, "%d", &i), 1);
		EXPECT_EQ(i, -2147483647);

		pclose(palout);
	}

	TEST(CodegenTest, TestOrd)
	{
		ofstream testfile("test/asc/test.pal");

		testfile << "program test(input, output);" << endl;
		testfile << "type t = (a, b, c, d, e);" << endl;
		testfile << "begin" << endl;
		testfile << "  writeln(ord('a'));" << endl;
		testfile << "  writeln(ord('z'));" << endl;
		testfile << "  writeln(ord(a));" << endl;
		testfile << "  writeln(ord(e));" << endl;
		testfile << "  writeln(ord(true));" << endl;
		testfile << "  writeln(ord(false));" << endl;
		testfile << "  writeln(ord(69));" << endl;
		testfile << "end." << endl;

		testfile.close();

		FILE* palout = popen("bin/pal -n test/asc/test.pal", "r");
		ASSERT_NE(palout, (void*)0);

		int i;

		ASSERT_EQ(fscanf(palout, "%d", &i), 1);
		EXPECT_EQ(i, 97);
		ASSERT_EQ(fscanf(palout, "%d", &i), 1);
		EXPECT_EQ(i, 122);
		ASSERT_EQ(fscanf(palout, "%d", &i), 1);
		EXPECT_EQ(i, 0);
		ASSERT_EQ(fscanf(palout, "%d", &i), 1);
		EXPECT_EQ(i, 4);
		ASSERT_EQ(fscanf(palout, "%d", &i), 1);
		EXPECT_EQ(i, 1);
		ASSERT_EQ(fscanf(palout, "%d", &i), 1);
		EXPECT_EQ(i, 0);
		ASSERT_EQ(fscanf(palout, "%d", &i), 1);
		EXPECT_EQ(i, 69);

		pclose(palout);
	}

	TEST(CodegenTest, TestChr)
	{
		ofstream testfile("test/asc/test.pal");

		testfile << "program test(input, output);" << endl;
		testfile << "begin" << endl;
		testfile << "  write(chr(97));" << endl;
		testfile << "  write(chr(98));" << endl;
		testfile << "  write(chr(99));" << endl;
		testfile << "  write(chr(100));" << endl;
		testfile << "  writeln();" << endl;
		testfile << "end." << endl;

		testfile.close();

		FILE* palout = popen("bin/pal -n test/asc/test.pal", "r");
		ASSERT_NE(palout, (void*)0);

		char* buf = new char[256];
		size_t bufsize = 255;

		ASSERT_GT(getline(&buf, &bufsize, palout), 0);
		EXPECT_EQ(string(buf), "abcd\n"); 

		pclose(palout);
	}

	TEST(CodegenTest, TestTrunc)
	{
		ofstream testfile("test/asc/test.pal");

		testfile << "program test(input, output);" << endl;
		testfile << "begin" << endl;
		testfile << "  writeln(trunc(3.14159));" << endl;
		testfile << "  writeln(trunc(322.992));" << endl;
		testfile << "  writeln(trunc(-623.14159));" << endl;
		testfile << "  writeln(trunc(-9623.94159));" << endl;
		testfile << "end." << endl;

		testfile.close();

		FILE* palout = popen("bin/pal -n test/asc/test.pal", "r");
		ASSERT_NE(palout, (void*)0);

		int i;

		ASSERT_EQ(fscanf(palout, "%d", &i), 1);
		EXPECT_EQ(i, 3);
		ASSERT_EQ(fscanf(palout, "%d", &i), 1);
		EXPECT_EQ(i, 322);
		ASSERT_EQ(fscanf(palout, "%d", &i), 1);
		EXPECT_EQ(i, -623);
		ASSERT_EQ(fscanf(palout, "%d", &i), 1);
		EXPECT_EQ(i, -9623);

		pclose(palout);
	}

	TEST(CodegenTest, TestRound)
	{
		ofstream testfile("test/asc/round.pal");

		testfile << "program test(input, output);" << endl;
		testfile << "begin" << endl;
		testfile << "  writeln(round(3.14159));" << endl;
		testfile << "  writeln(round(322.992));" << endl;
		testfile << "  writeln(round(-623.14159));" << endl;
		testfile << "  writeln(round(-9623.94159));" << endl;
		testfile << "end." << endl;

		testfile.close();

		FILE* palout = popen("bin/pal -n test/asc/round.pal", "r");
		ASSERT_NE(palout, (void*)0);

		int i;

		ASSERT_EQ(fscanf(palout, "%d", &i), 1);
		EXPECT_EQ(i, 3);
		ASSERT_EQ(fscanf(palout, "%d", &i), 1);
		EXPECT_EQ(i, 323);
		ASSERT_EQ(fscanf(palout, "%d", &i), 1);
		EXPECT_EQ(i, -623);
		ASSERT_EQ(fscanf(palout, "%d", &i), 1);
		EXPECT_EQ(i, -9624);

		pclose(palout);
	}

	TEST(CodegenTest, TestSuccPred)
	{
		ofstream testfile("test/asc/test.pal");

		testfile << "program test(input, output);" << endl;
		testfile << "type t = (a, b, c, d, e);" << endl;
		testfile << "begin" << endl;

		testfile << "	writeln(succ(69));" << endl;
		testfile << "	writeln(succ(-69));" << endl;
		testfile << "	writeln(pred(69));" << endl;
		testfile << "	writeln(pred(-69));" << endl;

		testfile << "	write(succ('q'));" << endl;
		testfile << "	write(succ('v'));" << endl;
		testfile << "	write(pred('q'));" << endl;
		testfile << "	write(pred('v'));" << endl;
		testfile << "	writeln();" << endl;

		testfile << "  if (succ(c) = d) then" << endl;
		testfile << "		writeln(10);" << endl;
		testfile << "  if (succ(d) = e) then" << endl;
		testfile << "		writeln(20);" << endl;
		testfile << "  if (pred(c) = b) then" << endl;
		testfile << "		writeln(30);" << endl;
		testfile << "  if (pred(b) = a) then" << endl;
		testfile << "		writeln(40);" << endl;

		testfile << "  if (succ(false) = true) then" << endl;
		testfile << "		writeln(50);" << endl;
		testfile << "  if (pred(true) = false) then" << endl;
		testfile << "		writeln(60);" << endl;
		testfile << "end." << endl;

		testfile.close();

		FILE* palout = popen("bin/pal -n test/asc/test.pal", "r");
		ASSERT_NE(palout, (void*)0);

		int i;
		char a;

		ASSERT_EQ(fscanf(palout, "%d", &i), 1);
		EXPECT_EQ(i, 70);
		ASSERT_EQ(fscanf(palout, "%d", &i), 1);
		EXPECT_EQ(i, -68);
		ASSERT_EQ(fscanf(palout, "%d", &i), 1);
		EXPECT_EQ(i, 68);
		ASSERT_EQ(fscanf(palout, "%d", &i), 1);
		EXPECT_EQ(i, -70);

		ASSERT_EQ(fscanf(palout, "%c", &a), 1); // eat newline

		ASSERT_EQ(fscanf(palout, "%c", &a), 1);
		EXPECT_EQ(a, 'r');
		ASSERT_EQ(fscanf(palout, "%c", &a), 1);
		EXPECT_EQ(a, 'w');
		ASSERT_EQ(fscanf(palout, "%c", &a), 1);
		EXPECT_EQ(a, 'p');
		ASSERT_EQ(fscanf(palout, "%c", &a), 1);
		EXPECT_EQ(a, 'u');

		ASSERT_EQ(fscanf(palout, "%d", &i), 1);
		EXPECT_EQ(i, 10);
		ASSERT_EQ(fscanf(palout, "%d", &i), 1);
		EXPECT_EQ(i, 20);
		ASSERT_EQ(fscanf(palout, "%d", &i), 1);
		EXPECT_EQ(i, 30);
		ASSERT_EQ(fscanf(palout, "%d", &i), 1);
		EXPECT_EQ(i, 40);

		ASSERT_EQ(fscanf(palout, "%d", &i), 1);
		EXPECT_EQ(i, 50);
		ASSERT_EQ(fscanf(palout, "%d", &i), 1);
		EXPECT_EQ(i, 60);

		pclose(palout);
	}

	TEST(CodegenTest, TestOdd)
	{
		ofstream testfile("test/asc/test.pal");

		testfile << "program test(input, output);" << endl;
		testfile << "begin" << endl;

		testfile << "  if (odd(0)) then" << endl;
		testfile << "		writeln(0);" << endl;
		testfile << "  if (odd(1)) then" << endl;
		testfile << "		writeln(1);" << endl;
		testfile << "  if (odd(2)) then" << endl;
		testfile << "		writeln(2);" << endl;
		testfile << "  if (odd(3)) then" << endl;
		testfile << "		writeln(3);" << endl;
		testfile << "  if (odd(4)) then" << endl;
		testfile << "		writeln(4);" << endl;
		testfile << "  if (odd(-12)) then" << endl;
		testfile << "		writeln(-12);" << endl;
		testfile << "  if (odd(-13)) then" << endl;
		testfile << "		writeln(-13);" << endl;
		testfile << "  if (odd(-69)) then" << endl;
		testfile << "		writeln(-69);" << endl;
		testfile << "  if (odd(68)) then" << endl;
		testfile << "		writeln(68);" << endl;
		testfile << "  if (odd(69)) then" << endl;
		testfile << "		writeln(69);" << endl;
		testfile << "end." << endl;

		testfile.close();

		FILE* palout = popen("bin/pal -n test/asc/test.pal", "r");
		ASSERT_NE(palout, (void*)0);

		int i;

		ASSERT_EQ(fscanf(palout, "%d", &i), 1);
		EXPECT_EQ(i, 1);
		ASSERT_EQ(fscanf(palout, "%d", &i), 1);
		EXPECT_EQ(i, 3);
		ASSERT_EQ(fscanf(palout, "%d", &i), 1);
		EXPECT_EQ(i, -13);
		ASSERT_EQ(fscanf(palout, "%d", &i), 1);
		EXPECT_EQ(i, -69);
		ASSERT_EQ(fscanf(palout, "%d", &i), 1);
		EXPECT_EQ(i, 69);

		pclose(palout);
	}

	TEST(CodegenTest, TestAbs)
	{
		ofstream testfile("test/asc/test.pal");

		testfile << "program test(input, output);" << endl;
		testfile << "begin" << endl;
		testfile << "  writeln(abs(5));" << endl;
		testfile << "  writeln(abs(-5));" << endl;
		testfile << "  writeln(abs(69));" << endl;
		testfile << "  writeln(abs(-69));" << endl;
		testfile << "  writeln(abs(69.69));" << endl;
		testfile << "  writeln(abs(-69.69));" << endl;
		testfile << "  writeln(abs(3.14159));" << endl;
		testfile << "  writeln(abs(-3.14159));" << endl;
		testfile << "end." << endl;

		testfile.close();

		FILE* palout = popen("bin/pal -S -n test/asc/test.pal", "r");
		ASSERT_NE(palout, (void*)0);

		int i;
		float f;

		ASSERT_EQ(fscanf(palout, "%d", &i), 1);
		EXPECT_EQ(i, 5);
		ASSERT_EQ(fscanf(palout, "%d", &i), 1);
		EXPECT_EQ(i, 5);
		ASSERT_EQ(fscanf(palout, "%d", &i), 1);
		EXPECT_EQ(i, 69);
		ASSERT_EQ(fscanf(palout, "%d", &i), 1);
		EXPECT_EQ(i, 69);
		ASSERT_EQ(fscanf(palout, "%f", &f), 1);
		EXPECT_FLOAT_EQ(f, 69.69);
		ASSERT_EQ(fscanf(palout, "%f", &f), 1);
		EXPECT_FLOAT_EQ(f, 69.69);
		ASSERT_EQ(fscanf(palout, "%f", &f), 1);
		EXPECT_FLOAT_EQ(f, 3.14159);
		ASSERT_EQ(fscanf(palout, "%f", &f), 1);
		EXPECT_FLOAT_EQ(f, 3.14159);

		pclose(palout);
	}

	TEST(CodegenTest, TestSqr)
	{
		ofstream testfile("test/asc/test.pal");

		testfile << "program test(input, output);" << endl;
		testfile << "begin" << endl;
		testfile << "  writeln(sqr(2));" << endl;
		testfile << "  writeln(sqr(-3));" << endl;
		testfile << "  writeln(sqr(4));" << endl;
		testfile << "  writeln(sqr(-9));" << endl;

		testfile << "  writeln(sqr(3.14159));" << endl;
		testfile << "  writeln(sqr(-3.14159));" << endl;
		testfile << "  writeln(sqr(10.0));" << endl;
		testfile << "  writeln(sqr(-10.0));" << endl;
		testfile << "end." << endl;

		testfile.close();

		FILE* palout = popen("bin/pal -S -n test/asc/test.pal", "r");
		ASSERT_NE(palout, (void*)0);

		int i;
		float f;

		ASSERT_EQ(fscanf(palout, "%d", &i), 1);
		EXPECT_EQ(i, 4);
		ASSERT_EQ(fscanf(palout, "%d", &i), 1);
		EXPECT_EQ(i, 9);
		ASSERT_EQ(fscanf(palout, "%d", &i), 1);
		EXPECT_EQ(i, 16);
		ASSERT_EQ(fscanf(palout, "%d", &i), 1);
		EXPECT_EQ(i, 81);

		ASSERT_EQ(fscanf(palout, "%f", &f), 1);
		EXPECT_FLOAT_EQ(f, 9.86958772809999);
		ASSERT_EQ(fscanf(palout, "%f", &f), 1);
		EXPECT_FLOAT_EQ(f, 9.86958772809999);
		ASSERT_EQ(fscanf(palout, "%f", &f), 1);
		EXPECT_FLOAT_EQ(f, 100.0);
		ASSERT_EQ(fscanf(palout, "%f", &f), 1);
		EXPECT_FLOAT_EQ(f, 100.0);

		pclose(palout);
	}

	TEST(CodegenTest, TestSqrt)
	{
		ofstream testfile("test/asc/test.pal");

		testfile << "program test(input, output);" << endl;
		testfile << "begin" << endl;
		testfile << "  writeln(sqrt(9.0));" << endl;
		testfile << "  writeln(sqrt(16.0));" << endl;
		testfile << "  writeln(sqrt(25.0));" << endl;
		testfile << "  writeln(sqrt(7.0));" << endl;
		testfile << "  writeln(sqrt(11.0));" << endl;
		testfile << "  writeln(sqrt(-1.0));" << endl;
		testfile << "end." << endl;

		testfile.close();

		FILE* palout = popen("bin/pal -S -n test/asc/test.pal", "r");
		ASSERT_NE(palout, (void*)0);

		float f;
		char c;

		ASSERT_EQ(fscanf(palout, "%f", &f), 1);
		EXPECT_NEAR(f, 3.0, 0.001);
		ASSERT_EQ(fscanf(palout, "%f", &f), 1);
		EXPECT_NEAR(f, 4.0, 0.001);
		ASSERT_EQ(fscanf(palout, "%f", &f), 1);
		EXPECT_NEAR(f, 5.0, 0.001);
		ASSERT_EQ(fscanf(palout, "%f", &f), 1);
		EXPECT_NEAR(f, 2.6457513110645907, 0.001);
		ASSERT_EQ(fscanf(palout, "%f", &f), 1);
		EXPECT_NEAR(f, 3.3166247903554, 0.001);

		ASSERT_EQ(fscanf(palout, "%c", &c), 1); // eat newline

		char str [1000];
		fgets(str, 300 , palout);
		EXPECT_STREQ(str, "Sqrt: Argument cannot be negative.\n");

		pclose(palout);
	}

	TEST(CodegenTest, TestSin)
	{
		ofstream testfile("test/asc/test.pal");

		testfile << "program test(input, output);" << endl;
		testfile << "const pi = 3.141592653589793;" << endl;
		testfile << "begin" << endl;
		testfile << "  writeln(sin(pi));" << endl;
		testfile << "  writeln(sin(-pi));" << endl;
		testfile << "  writeln(sin(pi/2));" << endl;
		testfile << "  writeln(sin(-pi/2));" << endl;
		testfile << "end." << endl;

		testfile.close();

		FILE* palout = popen("bin/pal -S -n test/asc/test.pal", "r");
		ASSERT_NE(palout, (void*)0);

		float f;
		char c;

		ASSERT_EQ(fscanf(palout, "%f", &f), 1);
		EXPECT_NEAR(f, 0.0, 0.001);
		ASSERT_EQ(fscanf(palout, "%f", &f), 1);
		EXPECT_NEAR(f, 0.0, 0.001);
		ASSERT_EQ(fscanf(palout, "%f", &f), 1);
		EXPECT_NEAR(f, 1.0, 0.001);
		ASSERT_EQ(fscanf(palout, "%f", &f), 1);
		EXPECT_NEAR(f, -1.0, 0.001);

		pclose(palout);
	}

	TEST(CodegenTest, TestExp)
	{
		ofstream testfile("test/asc/testexp.pal");

		testfile << "program test(input, output);" << endl;
		testfile << "begin" << endl;
		testfile << "  writeln(exp(0.0));" << endl;
		testfile << "  writeln(exp(-10.0));" << endl;
		testfile << "  writeln(exp(2.0));" << endl;
		testfile << "  writeln(exp(3.0));" << endl;
		testfile << "end." << endl;

		testfile.close();

		FILE* palout = popen("bin/pal -S -n test/asc/testexp.pal", "r");
		ASSERT_NE(palout, (void*)0);

		float f;
		char c;

		// FIXME -- something is horribly wrong with how exp() and ln() are being invoked...

		ASSERT_EQ(fscanf(palout, "%f", &f), 1);
		EXPECT_NEAR(f, 1, 0.001);
		ASSERT_EQ(fscanf(palout, "%f", &f), 1);
		EXPECT_NEAR(f, 0.0, 0.001);
		ASSERT_EQ(fscanf(palout, "%f", &f), 1);
		EXPECT_NEAR(f, 7.38905609893065, 0.001);
		ASSERT_EQ(fscanf(palout, "%f", &f), 1);
		EXPECT_NEAR(f, 20.085536923187668, 0.001);

		pclose(palout);
	}

	TEST(CodegenTest, TestLn)
	{
		ofstream testfile("test/asc/testln.pal");

		testfile << "program test(input, output);" << endl;
		testfile << "begin" << endl;
		testfile << "  writeln(ln(1.0));" << endl;
		testfile << "  writeln(ln(2.0));" << endl;
		//testfile << "  writeln(ln(4.0));" << endl; // FIXME !! hangs on 4!!!
		testfile << "  writeln(ln(6.0));" << endl;
		testfile << "  writeln(ln(10.0));" << endl;
		testfile << "end." << endl;

		testfile.close();

		FILE* palout = popen("bin/pal -S -n test/asc/testln.pal", "r");
		ASSERT_NE(palout, (void*)0);

		float f;
		char c;

		ASSERT_EQ(fscanf(palout, "%f", &f), 1);
		EXPECT_NEAR(f, 0, 0.001);
		ASSERT_EQ(fscanf(palout, "%f", &f), 1);
		EXPECT_NEAR(f, 0.6931471805599453, 0.001);
		//ASSERT_EQ(fscanf(palout, "%f", &f), 1);
		//EXPECT_NEAR(f, 1.3862943611198906, 0.001);
		ASSERT_EQ(fscanf(palout, "%f", &f), 1);
		EXPECT_NEAR(f, 1.791759469228055, 0.001);
		ASSERT_EQ(fscanf(palout, "%f", &f), 1);
		EXPECT_NEAR(f, 2.302585092994046, 0.001);

		pclose(palout);
	}
}

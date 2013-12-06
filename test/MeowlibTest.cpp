#include <fstream>
#include <stdio.h>
#include <math.h>

#include "gtest/gtest.h"

using namespace std;

namespace Meow
{
	TEST(MeowlibTest, TestOdd)
	{
		ifstream odd_source("asc/meowlib/odd.asc");
		ifstream abs_source("asc/meowlib/abs.asc");
		ofstream testfile("test/asc/odd_test.asc");

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

		testfile << "\tCONSTI -1" << endl;
		testfile << "\tCALL 0, ml_odd" << endl;
		testfile << "\tWRITEI" << endl;
		// expect 1

		testfile << "\tCONSTI -300" << endl;
		testfile << "\tCALL 0, ml_odd" << endl;
		testfile << "\tWRITEI" << endl;
		// expect 0

		testfile << "\tSTOP" << endl;

		// append builtin function implmentation
		testfile << abs_source.rdbuf();	
		testfile << odd_source.rdbuf();

		testfile.close();
		abs_source.close();
		odd_source.close();

		FILE* ascout = popen("cat test/asc/odd_test.asc | bin/asc", "r");
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

		ASSERT_EQ(fscanf(ascout, "%d", &retval), 1);
		EXPECT_EQ(retval, 1);

		ASSERT_EQ(fscanf(ascout, "%d", &retval), 1);
		EXPECT_EQ(retval, 0);

		pclose(ascout);
	}

	TEST(MeowlibTest, TestLn)
	{
		ifstream exp_source("asc/meowlib/exp.asc");
		ifstream ln_source("asc/meowlib/ln.asc");
		ofstream testfile("test/asc/ln_test.asc");

		testfile << "\tCONSTR 1.0" << endl;
		testfile << "\tCALL 0, ml_ln" << endl;
		testfile << "\tWRITER" << endl;
		testfile << "\tCONSTI 32" << endl;
		testfile << "\tWRITEC" << endl;
		// 0.000000
		
		testfile << "\tCONSTR 2.0" << endl;
		testfile << "\tCALL 0, ml_ln" << endl;
		testfile << "\tWRITER" << endl;
		testfile << "\tCONSTI 32" << endl;
		testfile << "\tWRITEC" << endl;
		// 0.693147

		testfile << "\tCONSTR 40.0" << endl;
		testfile << "\tCALL 0, ml_ln" << endl;
		testfile << "\tWRITER" << endl;
		testfile << "\tCONSTI 32" << endl;
		testfile << "\tWRITEC" << endl;
		testfile << "\tSTOP" << endl;
		// 3.688880

		testfile << exp_source.rdbuf();
		testfile << ln_source.rdbuf();

		testfile.close();
		exp_source.close();
		ln_source.close();

		FILE* ascout = popen("cat test/asc/ln_test.asc | bin/asc", "r");
		ASSERT_NE(ascout, (void*)0);

		float result;

		ASSERT_EQ(fscanf(ascout, "%f", &result), 1);
		ASSERT_TRUE(fabs(result - log(1)) < 0.000001);

		ASSERT_EQ(fscanf(ascout, "%f", &result), 1);
		ASSERT_TRUE(fabs(result - log(2)) < 0.000001);

		ASSERT_EQ(fscanf(ascout, "%f", &result), 1);
		ASSERT_TRUE(fabs(result - log(40)) < 0.000001);

		pclose(ascout);
	}
	
	TEST(MeowlibTest, TestSucc)
	{
		/* Unfortunately succ isn't actually supposed to
		 * work for reals, only for ordinals! 
		 * (ints, chars, bools, enums)

		ifstream ascsource("asc/meowlib/succ.asc");
		ofstream testfile("test/asc/test.asc");

		testfile << "\tCONSTR 0.0" << endl;
		testfile << "\tCALL 0, ml_succ" << endl;
		testfile << "\tWRITER" << endl;
		testfile << "\tCONSTI 32" << endl;
		testfile << "\tWRITEC" << endl;
		// 1.000000
		
		testfile << "\tCONSTR -1" << endl;
		testfile << "\tCALL 0, ml_succ" << endl;
		testfile << "\tWRITER" << endl;
		testfile << "\tCONSTI 32" << endl;
		testfile << "\tWRITEC" << endl;
		// 0.000000

		testfile << "\tCONSTR 1" << endl;
		testfile << "\tCALL 0, ml_succ" << endl;
		testfile << "\tWRITER" << endl;
		testfile << "\tCONSTI 32" << endl;
		testfile << "\tWRITEC" << endl;
		// 2.000000
		
		testfile << "\tCONSTR 99" << endl;
		testfile << "\tCALL 0, ml_succ" << endl;
		testfile << "\tWRITER" << endl;
		testfile << "\tCONSTI 32" << endl;
		testfile << "\tWRITEC" << endl;
		testfile << "\tSTOP" << endl;
		// 100.000000

		testfile << ascsource.rdbuf();

		testfile.close();
		ascsource.close();

		FILE* ascout = popen("cat test/asc/test.asc | bin/asc", "r");
		ASSERT_NE(ascout, (void*)0);

		float result;

		ASSERT_EQ(fscanf(ascout, "%f", &result), 1);
		ASSERT_TRUE(fabs(result - 1.0) < 0.000001);

		ASSERT_EQ(fscanf(ascout, "%f", &result), 1);
		ASSERT_TRUE(fabs(result - 0.0) < 0.000001);

		ASSERT_EQ(fscanf(ascout, "%f", &result), 1);
		ASSERT_TRUE(fabs(result - 2.0) < 0.000001);
		
		ASSERT_EQ(fscanf(ascout, "%f", &result), 1);
		ASSERT_TRUE(fabs(result - 100.0) < 0.000001);

		pclose(ascout);
		*/
	}

	TEST(MeowlibTest, TestAbs)
	{
		ifstream ascsource("asc/meowlib/abs.asc");
		ofstream testfile("test/asc/test.asc");

		testfile << "\tCONSTR 0.0" << endl;
		testfile << "\tCALL 0, ml_abs_real" << endl;
		testfile << "\tWRITER" << endl;
		testfile << "\tCONSTI 32" << endl;
		testfile << "\tWRITEC" << endl;
		// 0.00000
		
		testfile << "\tCONSTR -1" << endl;
		testfile << "\tCALL 0, ml_abs_real" << endl;
		testfile << "\tWRITER" << endl;
		testfile << "\tCONSTI 32" << endl;
		testfile << "\tWRITEC" << endl;
		// 1.00000

		testfile << "\tCONSTR 1" << endl;
		testfile << "\tCALL 0, ml_abs_real" << endl;
		testfile << "\tWRITER" << endl;
		testfile << "\tCONSTI 32" << endl;
		testfile << "\tWRITEC" << endl;
		// 1.000000
		
		testfile << "\tCONSTR -1000" << endl;
		testfile << "\tCALL 0, ml_abs_real" << endl;
		testfile << "\tWRITER" << endl;
		testfile << "\tCONSTI 32" << endl;
		testfile << "\tWRITEC" << endl;
		testfile << "\tSTOP" << endl;
		// 1000.000000

		testfile << ascsource.rdbuf();

		testfile.close();
		ascsource.close();

		FILE* ascout = popen("cat test/asc/test.asc | bin/asc", "r");
		ASSERT_NE(ascout, (void*)0);

		float result;

		ASSERT_EQ(fscanf(ascout, "%f", &result), 1);
		ASSERT_TRUE(fabs(result - 0.0) < 0.000001);

		ASSERT_EQ(fscanf(ascout, "%f", &result), 1);
		ASSERT_TRUE(fabs(result - 1.0) < 0.000001);

		ASSERT_EQ(fscanf(ascout, "%f", &result), 1);
		ASSERT_TRUE(fabs(result - 1.0) < 0.000001);
		
		ASSERT_EQ(fscanf(ascout, "%f", &result), 1);
		ASSERT_TRUE(fabs(result - 1000.0) < 0.000001);

		pclose(ascout);
	}
	
	TEST(MeowlibTest, TestSin)
	{
		ifstream ascsource("asc/meowlib/sin.asc");
		ofstream testfile("test/asc/test.asc");

		testfile << "\tCONSTR 0.0" << endl;
		testfile << "\tCALL 0, ml_sin" << endl;
		testfile << "\tWRITER" << endl;
		testfile << "\tCONSTI 32" << endl;
		testfile << "\tWRITEC" << endl;
		// 0.00000
		
		testfile << "\tCONSTR 1.0" << endl;
		testfile << "\tCALL 0, ml_sin" << endl;
		testfile << "\tWRITER" << endl;
		testfile << "\tCONSTI 32" << endl;
		testfile << "\tWRITEC" << endl;
		// 0.841471

		testfile << "\tCONSTR -1.0" << endl;
		testfile << "\tCALL 0, ml_sin" << endl;
		testfile << "\tWRITER" << endl;
		testfile << "\tCONSTI 32" << endl;
		testfile << "\tWRITEC" << endl;
		// -0.841471
		
		testfile << "\tCONSTR -5" << endl;
		testfile << "\tCALL 0, ml_sin" << endl;
		testfile << "\tWRITER" << endl;
		testfile << "\tCONSTI 32" << endl;
		testfile << "\tWRITEC" << endl;
		testfile << "\tSTOP" << endl;
		// -0.958924

		testfile << ascsource.rdbuf();

		testfile.close();
		ascsource.close();

		FILE* ascout = popen("cat test/asc/test.asc | bin/asc", "r");
		ASSERT_NE(ascout, (void*)0);

		float result;

		ASSERT_EQ(fscanf(ascout, "%f", &result), 1);
		ASSERT_TRUE(fabs(result - sin(0)) < 0.001);

		ASSERT_EQ(fscanf(ascout, "%f", &result), 1);
		ASSERT_TRUE(fabs(result - sin(1.0)) < 0.001);
		
		ASSERT_EQ(fscanf(ascout, "%f", &result), 1);
		ASSERT_TRUE(fabs(result - sin(-1.0)) < 0.001);
		
		ASSERT_EQ(fscanf(ascout, "%f", &result), 1);
		ASSERT_TRUE(fabs(result - sin(-5.0)) < 0.001);

		pclose(ascout);
	}
	
	TEST(MeowlibTest, TestSqr)
	{
		ifstream ascsource("asc/meowlib/sqr.asc");
		ofstream testfile("test/asc/test.asc");

		testfile << "\tCONSTR 0.0" << endl;
		testfile << "\tCALL 0, ml_sqr" << endl;
		testfile << "\tWRITER" << endl;
		testfile << "\tCONSTI 32" << endl;
		testfile << "\tWRITEC" << endl;
		// 0.00000
		
		testfile << "\tCONSTR -1.0" << endl;
		testfile << "\tCALL 0, ml_sqr" << endl;
		testfile << "\tWRITER" << endl;
		testfile << "\tCONSTI 32" << endl;
		testfile << "\tWRITEC" << endl;
		// 1.000000

		testfile << "\tCONSTR 2.0" << endl;
		testfile << "\tCALL 0, ml_sqr" << endl;
		testfile << "\tWRITER" << endl;
		testfile << "\tCONSTI 32" << endl;
		testfile << "\tWRITEC" << endl;
		// 4.000000
		
		testfile << "\tCONSTR -5" << endl;
		testfile << "\tCALL 0, ml_sqr" << endl;
		testfile << "\tWRITER" << endl;
		testfile << "\tCONSTI 32" << endl;
		testfile << "\tWRITEC" << endl;
		testfile << "\tSTOP" << endl;
		// 25.000

		testfile << ascsource.rdbuf();

		testfile.close();
		ascsource.close();

		FILE* ascout = popen("cat test/asc/test.asc | bin/asc", "r");
		ASSERT_NE(ascout, (void*)0);

		float result;

		ASSERT_EQ(fscanf(ascout, "%f", &result), 1);
		ASSERT_TRUE(fabs(result - 0) < 0.000001);

		ASSERT_EQ(fscanf(ascout, "%f", &result), 1);
		ASSERT_TRUE(fabs(result - 1.0) < 0.000001);
		
		ASSERT_EQ(fscanf(ascout, "%f", &result), 1);
		ASSERT_TRUE(fabs(result - 4.0) < 0.000001);
		
		ASSERT_EQ(fscanf(ascout, "%f", &result), 1);
		ASSERT_TRUE(fabs(result - 25.0) < 0.000001);

		pclose(ascout);
	}

	TEST(MeowlibTest, TestSqrt)
	{
		ifstream ascsource("asc/meowlib/sqrt.asc");
		ofstream testfile("test/asc/test.asc");

		testfile << "\tCONSTR 0.0" << endl;
		testfile << "\tCALL 0, ml_sqrt" << endl;
		testfile << "\tWRITER" << endl;
		testfile << "\tCONSTI 32" << endl;
		testfile << "\tWRITEC" << endl;
		// 0.00000
		
		testfile << "\tCONSTR 1.0" << endl;
		testfile << "\tCALL 0, ml_sqrt" << endl;
		testfile << "\tWRITER" << endl;
		testfile << "\tCONSTI 32" << endl;
		testfile << "\tWRITEC" << endl;
		// 1.000000

		testfile << "\tCONSTR 2.0" << endl;
		testfile << "\tCALL 0, ml_sqrt" << endl;
		testfile << "\tWRITER" << endl;
		testfile << "\tCONSTI 32" << endl;
		testfile << "\tWRITEC" << endl;
		// 1.414214
		
		testfile << "\tCONSTR 25" << endl;
		testfile << "\tCALL 0, ml_sqrt" << endl;
		testfile << "\tWRITER" << endl;
		testfile << "\tCONSTI 32" << endl;
		testfile << "\tWRITEC" << endl;
		testfile << "\tSTOP" << endl;
		// 5.000000

		testfile << ascsource.rdbuf();

		testfile.close();
		ascsource.close();

		FILE* ascout = popen("cat test/asc/test.asc | bin/asc", "r");
		ASSERT_NE(ascout, (void*)0);

		float result;

		ASSERT_EQ(fscanf(ascout, "%f", &result), 1);
		ASSERT_TRUE(fabs(result - sqrt(0.0)) < 0.005);

		ASSERT_EQ(fscanf(ascout, "%f", &result), 1);
		ASSERT_TRUE(fabs(result - sqrt(1.0)) < 0.005);
		
		ASSERT_EQ(fscanf(ascout, "%f", &result), 1);
		ASSERT_TRUE(fabs(result - sqrt(2.0)) < 0.005);
		
		ASSERT_EQ(fscanf(ascout, "%f", &result), 1);
		ASSERT_TRUE(fabs(result - sqrt(25.0)) < 0.005);

		pclose(ascout);
	}
	
	TEST(MeowlibTest, TestExp)
	{
		ifstream ascsource("asc/meowlib/exp.asc");
		ofstream testfile("test/asc/test.asc");

		testfile << "\tCONSTR 0.0" << endl;
		testfile << "\tCALL 0, ml_exp" << endl;
		testfile << "\tWRITER" << endl;
		testfile << "\tCONSTI 32" << endl;
		testfile << "\tWRITEC" << endl;
		// 0.00000
		
		testfile << "\tCONSTR 1.0" << endl;
		testfile << "\tCALL 0, ml_exp" << endl;
		testfile << "\tWRITER" << endl;
		testfile << "\tCONSTI 32" << endl;
		testfile << "\tWRITEC" << endl;
		// 2.718281

		testfile << "\tCONSTR -1.0" << endl;
		testfile << "\tCALL 0, ml_exp" << endl;
		testfile << "\tWRITER" << endl;
		testfile << "\tCONSTI 32" << endl;
		testfile << "\tWRITEC" << endl;
		// 0.367879
		
		testfile << "\tCONSTR 0.5" << endl;
		testfile << "\tCALL 0, ml_exp" << endl;
		testfile << "\tWRITER" << endl;
		testfile << "\tCONSTI 32" << endl;
		testfile << "\tWRITEC" << endl;
		// 1.658721
		
		testfile << "\tCONSTR 5.0" << endl;
		testfile << "\tCALL 0, ml_exp" << endl;
		testfile << "\tWRITER" << endl;
		testfile << "\tCONSTI 32" << endl;
		testfile << "\tWRITEC" << endl;
		testfile << "\tSTOP" << endl;
		// 148.413159

		testfile << ascsource.rdbuf();

		testfile.close();
		ascsource.close();

		FILE* ascout = popen("cat test/asc/test.asc | bin/asc", "r");
		ASSERT_NE(ascout, (void*)0);

		float result;

		ASSERT_EQ(fscanf(ascout, "%f", &result), 1);
		ASSERT_TRUE(fabs(result - exp(0.0)) < 0.000001);

		ASSERT_EQ(fscanf(ascout, "%f", &result), 1);
		ASSERT_TRUE(fabs(result - exp(1.0)) < 0.000001);
		
		ASSERT_EQ(fscanf(ascout, "%f", &result), 1);
		ASSERT_TRUE(fabs(result - exp(-1.0)) < 0.000001);
		
		ASSERT_EQ(fscanf(ascout, "%f", &result), 1);
		ASSERT_TRUE(fabs(result - exp(0.5)) < 0.000001);
		
		ASSERT_EQ(fscanf(ascout, "%f", &result), 1);
		ASSERT_TRUE(fabs(result - exp(5.0)) < 0.00001);

		pclose(ascout);
	}
	
	TEST(MeowlibTest, TestPred)
	{
		/* Unfortunately pred isn't actually supposed to
		 * work for reals, only for ordinals! 
		 * (ints, chars, bools, enums)

		ifstream ascsource("asc/meowlib/pred.asc");
		ofstream testfile("test/asc/pred_test.asc");

		testfile << "\tCONSTR 0.0" << endl;
		testfile << "\tCALL 0, ml_pred" << endl;
		testfile << "\tWRITER" << endl;
		testfile << "\tCONSTI 32" << endl;
		testfile << "\tWRITEC" << endl;
		// -1.000000
		
		testfile << "\tCONSTR 1.0" << endl;
		testfile << "\tCALL 0, ml_pred" << endl;
		testfile << "\tWRITER" << endl;
		testfile << "\tCONSTI 32" << endl;
		testfile << "\tWRITEC" << endl;
		// 0.000000

		testfile << "\tCONSTR -5" << endl;
		testfile << "\tCALL 0, ml_pred" << endl;
		testfile << "\tWRITER" << endl;
		testfile << "\tCONSTI 32" << endl;
		testfile << "\tWRITEC" << endl;
		// -6.000000
		
		testfile << "\tCONSTR 0.5" << endl;
		testfile << "\tCALL 0, ml_pred" << endl;
		testfile << "\tWRITER" << endl;
		testfile << "\tCONSTI 32" << endl;
		testfile << "\tWRITEC" << endl;
		testfile << "\tSTOP" << endl;
		// -0.500000

		testfile << ascsource.rdbuf();

		testfile.close();
		ascsource.close();

		FILE* ascout = popen("cat test/asc/pred_test.asc | bin/asc", "r");
		ASSERT_NE(ascout, (void*)0);

		float result;

		ASSERT_EQ(fscanf(ascout, "%f", &result), 1);
		ASSERT_TRUE(fabs(result - (-1.0)) < 0.000001);

		ASSERT_EQ(fscanf(ascout, "%f", &result), 1);
		ASSERT_TRUE(fabs(result - 0.0) < 0.000001);
		
		ASSERT_EQ(fscanf(ascout, "%f", &result), 1);
		ASSERT_TRUE(fabs(result - (-6.0)) < 0.000001);
		
		ASSERT_EQ(fscanf(ascout, "%f", &result), 1);
		ASSERT_TRUE(fabs(result - (-0.5)) < 0.000001);

		pclose(ascout);
		*/
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

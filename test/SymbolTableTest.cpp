#include <fstream>
#include "gtest/gtest.h"

#include "../src/SymbolTable.hpp"
#include "../src/Symbol.hpp"
#include "../src/EntryList.hpp"

using namespace std;

namespace Meow
{
	TEST(SymbolTableTest, addSymbolTest1)
	{

		SymbolTable table;
		Symbol * symbol = new Symbol();

		symbol->setName("i");
		symbol->setType("variable");
		
		table.addSymbol(symbol);

		symbol = NULL;

		symbol = table.getSymbolCurLevel("i");
		EXPECT_EQ(symbol->getName(),"i");
	}

	TEST(SymbolTableTest, addSymbolTest2)
	{
		SymbolTable table;
		Symbol * symbol = new Symbol();
	
		symbol->setName("x");
		symbol->setType("variable");

		table.addSymbol(symbol);
		symbol = NULL;
		table.incLevel();
		table.incLevel();
		table.incLevel();
		
		symbol = table.getSymbol("x");
		EXPECT_EQ(symbol->getType(), "variable");
	}

	TEST(SymbolTableTest, scopeChangeTest1)
	{
		SymbolTable table;
		Symbol * symbol = new Symbol();
		
		symbol->setName("myVar");
		symbol->setType("variable");

		table.addSymbol(symbol);

		table.incLevel();
		table.incLevel();
		symbol = new Symbol();
		symbol->setName("myVar");
		symbol->setType("function");

		table.addSymbol(symbol);
		symbol = NULL;

		symbol = table.getSymbol("myVar");
		EXPECT_EQ(symbol->getType(), "function");
		table.decLevel();
		symbol = table.getSymbol("myVar");
		EXPECT_EQ(symbol->getType(), "variable");
	}
}

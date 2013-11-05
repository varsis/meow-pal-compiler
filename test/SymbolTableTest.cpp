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
		symbol->setSymbolType(Symbol::Variable);
		
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
		symbol->setSymbolType(Symbol::Variable);

		table.addSymbol(symbol);
		symbol = NULL;
		table.incLevel();
		table.incLevel();
		table.incLevel();
		
		symbol = table.getSymbol("x");
		EXPECT_EQ(symbol->getSymbolType(), Symbol::Variable);
	}

	TEST(SymbolTableTest, scopeChangeTest1)
	{
		SymbolTable table;
		Symbol * symbol = new Symbol();
		
		symbol->setName("myVar");
		symbol->setSymbolType(Symbol::Variable);

		table.addSymbol(symbol);

		table.incLevel();
		table.incLevel();
		symbol = new Symbol();
		symbol->setName("myVar");
		symbol->setSymbolType(Symbol::Procedure);

		table.addSymbol(symbol);
		symbol = NULL;

		symbol = table.getSymbol("myVar");
		EXPECT_EQ(symbol->getSymbolType(), Symbol::Procedure);
		table.decLevel();
		symbol = table.getSymbol("myVar");
		EXPECT_EQ(symbol->getSymbolType(), Symbol::Variable);
	}

	TEST(SymbolTableTest, scopeChangeTest2)
	{
		SymbolTable table;
		Symbol * symbol = new Symbol("myFunc", Symbol::Procedure);

		table.addSymbol(symbol);

		table.incLevel();
		
		symbol = new Symbol("myFunc", Symbol::Procedure);

		table.addSymbol(symbol);

		symbol = NULL;
		symbol = table.getSymbol("myFunc");
		EXPECT_EQ(symbol->getLexLevel(), 1);

		table.decLevel();
		symbol = NULL;
		symbol = table.getSymbol("myFunc");
		EXPECT_EQ(symbol->getLexLevel(), 0);
	}

	TEST(SymbolTableTest, symbolLookup0)
	{
		SymbolTable table;
		Symbol * symbol;

		symbol = table.getSymbol("myVar");

		EXPECT_EQ(symbol, (Symbol *) NULL);

		symbol = new Symbol("myVar", Symbol::Variable);
		table.addSymbol(symbol);
		table.incLevel();
		symbol = table.getSymbolCurLevel("myVar");

		EXPECT_EQ(symbol, (Symbol *) NULL);
	}

	TEST(SymbolTableTest, symbolRedef)
	{
		SymbolTable table;
		Symbol * symbol = new Symbol("myVar", Symbol::Variable);

		table.addSymbol(symbol);
		table.incLevel();

		symbol = new Symbol("myVar", Symbol::Procedure);
		table.addSymbol(symbol);
		
		symbol = new Symbol("myVar", Symbol::Procedure);
		table.addSymbol(symbol);
		symbol = table.getSymbol("myVar");
		
		EXPECT_EQ(symbol->getSymbolType(), Symbol::Procedure);
		
		table.decLevel();
		symbol = table.getSymbol("myVar");
		
		EXPECT_EQ(symbol->getSymbolType(), Symbol::Variable);
	}
		

}

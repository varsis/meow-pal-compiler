#include "SymbolTable.hpp"
#include "EntryList.hpp"
#include <string>
#include "Type.hpp"

extern int g_varOffset;

namespace Meow
{
	SymbolTable::SymbolTable()
	{
		m_currentLevel = 0;
	}

	SymbolTable::~SymbolTable()
	{
		SymbolMap::iterator i;

		// Go through the table and delete all the entry lists
		for(i=m_symbolTable.begin(); i != m_symbolTable.end(); i++)
		{
			delete i->second;
		}
	}

	void SymbolTable::addSymbol(Symbol * symbol)
	{
		EntryList* list;

		// Make sure that we have allocated space 
		// if the name hasn't been seen
		if (m_symbolTable.count(symbol->getName()) == 0)
		{
			list = new EntryList();
			m_symbolTable[symbol->getName()] = list;
		}
		else 
		{
			list = m_symbolTable[symbol->getName()];
		}

		list->addEntry(symbol, m_currentLevel);
	}

	Symbol* SymbolTable::getSymbolCurLevel(std::string name)
	{
		EntryList* list;
		
		// If we know its not in any scope
		if (m_symbolTable.count(name) == 0)
		{
			return NULL;
		}

		list = m_symbolTable[name];
		return list->getCurLevelEntry(m_currentLevel);
	}

	Symbol* SymbolTable::getSymbol(std::string name)
	{
		EntryList* list;

		// If we know its not in any scope
		if (m_symbolTable.count(name) == 0)
		{
			return NULL;
		}

		list = m_symbolTable[name];
		return list->getEntry();
	}

	void SymbolTable::incLevel() 
	{
		m_currentLevel++;
	}

	void SymbolTable::decLevel()
	{
		SymbolMap::iterator i;
		
		// Make sure that we aren't at zero since -1 scope is wrong
		if (m_currentLevel != 0)
		{
			m_currentLevel--;
		}

		// Set all the entry (scope) lists to max of current level
		for(i=m_symbolTable.begin(); i != m_symbolTable.end(); i++)
		{
			i->second->setLexLevel(m_currentLevel);
		}
	}

	int SymbolTable::getCurLevel()
	{
		return m_currentLevel;
	}

	void SymbolTable::allocateSpace(Symbol* sym, Type* type)
	{
		if (sym && type)
		{
			sym->setSizeInMem(type->getTypeSize());
			sym->setLocation(g_varOffset);
			g_varOffset += type->getTypeSize();
		}
	}
}

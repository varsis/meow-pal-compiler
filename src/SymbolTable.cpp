#include "SymbolTable.hpp"
#include "EntryList.hpp"
#include <string>

namespace Meow
{
	SymbolTable::SymbolTable()
	{
		m_currentLevel = 0;
	}

	SymbolTable::~SymbolTable()
	{
		m_symbolTable.erase(m_symbolTable.begin(), m_symbolTable.end());
	}

	void SymbolTable::addSymbol(Symbol * symbol)
	{
		EntryList* list;

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

		if (m_symbolTable.count(name) == 0)
		{
			return NULL;
		}

		list = m_symbolTable[name];
		return list->getEntry(m_currentLevel);
	}

	Symbol* SymbolTable::getSymbol(std::string name)
	{
		EntryList* list;
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
		std::tr1::unordered_map<std::string, EntryList*>::iterator i;
		if (m_currentLevel != 0)
		{
			m_currentLevel--;
		}

		for(i=m_symbolTable.begin(); i != m_symbolTable.end(); i++)
		{
			i->second->setLexLevel(m_currentLevel);
		}
	}

	int SymbolTable::getCurLevel()
	{
		return m_currentLevel;
	}

}



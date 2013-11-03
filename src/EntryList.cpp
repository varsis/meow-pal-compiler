#include "EntryList.hpp"
#include "Symbol.hpp"

namespace Meow
{
	EntryList::~EntryList()
	{
		// Go through the entrys and delete them
		for(int i=0; i< (int) m_list.size(); i++)
		{
			if (m_list[i] != NULL)
			{
				delete m_list[i];
			}
		}
	}
	
	Symbol* EntryList::getCurLevelEntry(int level)
	{
		// If the list has at list one entry
		if (m_list.size() > 0)
		{
			// Return the last entry if the scope level matches
			if (m_list[m_list.size()-1]->getLexLevel() == level)
			{
				return m_list[m_list.size()-1];
			}
		}

		return NULL;
	}

	Symbol * EntryList::getEntry()
	{
		// Get the last entry entered (highest scope) if any
		if (m_list.size() > 0)
		{
			return m_list[m_list.size()-1];
		}

		return NULL;
	}


	void EntryList::addEntry(Symbol * symbol, int level)
	{
		// Override the lexical level and add to list
		symbol->setLexLevel(level);
		m_list.push_back(symbol);
	}

	void EntryList::setLexLevel(int level)
	{
		// Go through the list in reverse and delete everything
		// until we find a symbol that is in level
		for(int i = (int) m_list.size()-1; i>=0; i--)
		{
			if (m_list[i]->getLexLevel() > level)
			{
				delete m_list[i];
				m_list.resize(m_list.size()-1);
			}
			else
			{
				break;
			}
		}
	}
}

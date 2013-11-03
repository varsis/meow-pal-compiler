#include "EntryList.hpp"
#include "Symbol.hpp"

namespace Meow
{
	EntryList::~EntryList()
	{
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
		if (m_list.size() > 0)
		{
			if (m_list[m_list.size()-1]->getLexLevel() == level)
			{
				return m_list[m_list.size()-1];
			}
		}

		return NULL;
	}

	Symbol * EntryList::getEntry()
	{
		if (m_list.size() > 0)
		{
			return m_list[m_list.size()-1];
		}

		return NULL;
	}


	void EntryList::addEntry(Symbol * symbol, int level)
	{
		symbol->setLexLevel(level);
		m_list.push_back(symbol);
	}

	void EntryList::setLexLevel(int level)
	{
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

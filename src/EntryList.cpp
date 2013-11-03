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
	
	Symbol* EntryList::getEntry(int level)
	{
		if (level >= (int)m_list.size())
		{
			return NULL;
		}
		return m_list[level];
	}

	Symbol * EntryList::getEntry()
	{
		for(int i=(m_list.size()-1); i>=0; i--)
		{
			if (m_list[i] != NULL)
			{
				return m_list[i];
			}
		}
		return NULL;
	}


	void EntryList::addEntry(Symbol * symbol, int level)
	{
		for(int i=m_list.size(); i<level; i++)
		{
			m_list.push_back(NULL);
		}
		m_list.push_back(symbol);
	}

	void EntryList::setLexLevel(int level)
	{
		m_list.resize(level+1);
	}
}

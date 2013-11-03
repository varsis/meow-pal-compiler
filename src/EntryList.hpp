#ifndef ENTRYLIST_HPP
#define ENTRYLIST_HPP

#include <string>
#include <vector>

namespace Meow
{
	class Symbol;

	class EntryList
	{
		private:
			std::vector<Symbol*> m_list;
		
		public:
			~EntryList();
			Symbol* getCurLevelEntry(int);
			Symbol* getEntry();
			void addEntry(Symbol*, int);
			void setLexLevel(int);
	};

}

#endif

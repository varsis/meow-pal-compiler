#ifndef SYMBOL_TABLE_HPP
#define SYMBOL_TABLE_HPP

#include "EntryList.hpp"
#include "Symbol.hpp"
#include "Type.hpp"

#ifndef NO_TR1
#include <tr1/unordered_map>
#else
#include <unordered_map>
#endif
#include <string>

namespace Meow
{

#ifndef NO_TR1
	typedef std::tr1::unordered_map<std::string, EntryList*> SymbolMap;
#else
	typedef std::unordered_map<std::string, EntryList*> SymbolMap;
#endif
	class SymbolTable
	{

		public:
			SymbolTable();
			~SymbolTable();
			void addSymbol(Symbol * symbol);
			Symbol* getSymbolCurLevel(std::string name);
			Symbol* getSymbol(std::string name);
			int getCurLevel();
			void incLevel();
			void decLevel();
			void incLocationCount(Symbol * sym);
			int getLocationCount();
			void allocateSpace(Symbol*, Type*);
		private:
			SymbolMap m_symbolTable;
			int m_currentLevel;
			// Contains the last location in mem.
			int m_locationLexCounter[16];
	};
}

#endif

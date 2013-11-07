#ifndef SYMBOL_TABLE_HPP
#define SYMBOL_TABLE_HPP

#include "EntryList.hpp"
#include "Symbol.hpp"
#ifndef NO_TR1
#include <tr1/unordered_map>
#else
#include <unordered_map>
#endif
#include <string>

namespace Meow
{

#ifndef USE_TR1
	typedef std::tr1::unordered_map<std::string, EntryList*> SymbolMap;
#else
	typedef std::unordered_map hash_map;
#endif
	class SymbolTable
	{
		private:
			SymbolMap m_symbolTable;
			int m_currentLevel;

		public:
			SymbolTable();
			~SymbolTable();
			void addSymbol(Symbol * symbol);
			Symbol* getSymbolCurLevel(std::string name);
			Symbol* getSymbol(std::string name);
			int getCurLevel();
			void incLevel();
			void decLevel();

		private:
	};
}

#endif

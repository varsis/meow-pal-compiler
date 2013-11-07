#ifndef SYMBOL_TABLE_HPP
#define SYMBOL_TABLE_HPP

#include "EntryList.hpp"
#include "Symbol.hpp"
#include <tr1/unordered_map>
#include <string>

namespace Meow
{
	class SymbolTable
	{
		private:
			std::tr1::unordered_map<std::string, EntryList*> m_symbolTable;
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

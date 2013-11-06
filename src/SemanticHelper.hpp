#ifndef SEMANTICHELPER_HPP
#define SEMANTICHELPER_HPP

#include <string>

namespace Meow
{

	class ErrorManager;
	class SymbolTable;
	class PalScanner;
	class Type;

	class SemanticHelper
	{
		public:
			SemanticHelper(PalScanner* scanner,
					ErrorManager* manager,
					SymbolTable* table);

			void addPredefinedSymbols();
			Type* getTypeFromID(std::string id);

		private:
			PalScanner* m_scanner;
			SymbolTable* m_table;
			ErrorManager* m_errorManager;
	};
}

#endif

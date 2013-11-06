#ifndef SEMANTICHELPER_HPP
#define SEMANTICHELPER_HPP

#include <string>

using namespace std;

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

			void defineType(string id, Type* type);
			Type* getTypeForVarId(string id);
			Type* getTypeFromID(string id);

			void declareVariable(string id, Type* type);

		private:
			PalScanner* m_scanner;
			SymbolTable* m_table;
			ErrorManager* m_errorManager;
	};
}

#endif

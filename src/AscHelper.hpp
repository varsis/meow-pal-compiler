#ifndef ASCHELPER_HPP
#define ASCHELPER_HPP

#include <vector>
#include <string>

#include "Type.hpp"
#include "Symbol.hpp"
#include "SemanticHelper.hpp"

using namespace std;

namespace Meow
{
	class SymbolTable;

	class AscHelper
	{
		public:
			AscHelper(ofstream& ascOutput, SymbolTable* table, SemanticHelper* semanticHelper);

			void invokeProcedure(string procedureName, 
					InvocationParameters* params);

			ofstream& out() { return m_ascOutput; }

		private:
			ofstream& m_ascOutput;
			SymbolTable* m_symbolTable;
			SemanticHelper* m_semanticHelper;
			ErrorManager* m_errorManager;
	};
}

#endif

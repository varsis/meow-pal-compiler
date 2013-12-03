#ifndef ASCHELPER_HPP
#define ASCHELPER_HPP

#include <vector>
#include <string>

#include "Type.hpp"
#include "Symbol.hpp"
#include "SemanticHelper.hpp"
#include "Symbol.hpp"

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

			void invokeWrite(InvocationParameters* params);
			void invokeWriteln(InvocationParameters* params);

			void invokeRead(InvocationParameters* params);
			void invokeReadln(InvocationParameters* params);
			
			ofstream& out() { return m_ascOutput; }
			void simpleExpressionHelper(Type * typeOne, Type * typeTwo, string functionName);
			void simpleExpressionMod();

			std::string currentLabel(int offset = 0);
			void reserveLabels(int count);
			void popLabels();
			void allocVariable(Symbol*);
			void accessVariable(LValue lvalue);
			void pushConstantValue(Symbol* symbol);
			void assignToVariable(LValue lvalue);
			void addArraySubscriptOffset(Type* arrayType);
			void deallocVariables();

		private:
			ofstream& m_ascOutput;
			SymbolTable* m_symbolTable;
			SemanticHelper* m_semanticHelper;
			ErrorManager* m_errorManager;

			vector<int> m_labelStack;
			int m_nextLabel;
	};
}

#endif

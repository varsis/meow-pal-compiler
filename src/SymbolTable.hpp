#ifndef SYMBOL_TABLE_HPP
#define SYMBOL_TABLE_HPP

#include "EntryList.hpp"
#include "Symbol.hpp"
#include <tr1/unordered_map>
#include <string>

namespace Meow
{
	enum Operator
	{
		OpEQ,
		OpNE,
		OpLE,
		OpLT,
		OpGE,
		OpGT,

		OpADD,
		OpSUBTRACT,
		OpMULTIPLY,
		OpREALDIVIDE,
		OpINTDIVIDE,
		OpMOD,

		OpNOT,

			// etc..
	};

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

			TypeSymbol* getOpResultType(Operator op, TypeSymbol* type);
			TypeSymbol* getOpResultType(Operator op, TypeSymbol* leftType, TypeSymbol* rightType);

			bool checkCompatible(TypeSymbol* ltype, TypeSymbol* rtype);
			bool checkAssignmentCompatible(TypeSymbol* ltype, TypeSymbol* rtype);

			TypeSymbol* getRawBooleanType() { return &m_booleanType; }
			TypeSymbol* getRawIntegerType() { return &m_integerType; }
			TypeSymbol* getRawRealType() { return &m_realType; }
			TypeSymbol* getRawCharType() { return &m_charType; }
		private:

			// Predefined raw types
			TypeSymbol m_booleanType;
			TypeSymbol m_integerType;
			TypeSymbol m_realType;
			TypeSymbol m_charType;
			// TODO check for more?
	};
}

#endif

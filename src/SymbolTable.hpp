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

		OpPLUS,
		OpMINUS,

		OpADD,
		OpSUBTRACT,
		OpMULTIPLY,
		OpREALDIVIDE,
		OpINTDIVIDE,
		OpMOD,

		OpNOT,
		OpAND,
		OpOR
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

			// TODO move to semantic helper!
			Type* getOpResultType(Operator op, Type* type);
			Type* getOpResultType(Operator op, Type* leftType, Type* rightType);

			// TODO move to semantic helper!
			bool checkCompatible(Type* ltype, Type* rtype);
			bool checkAssignmentCompatible(Type* ltype, Type* rtype);

			// TODO move to semantic helper!
			Type* getRawBooleanType() { return &m_booleanType; }
			Type* getRawIntegerType() { return &m_integerType; }
			Type* getRawRealType() { return &m_realType; }
			Type* getRawCharType() { return &m_charType; }
		private:

			// Predefined raw types
			Type m_booleanType;
			Type m_integerType;
			Type m_realType;
			Type m_charType;
	};
}

#endif

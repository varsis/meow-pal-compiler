#ifndef SEMANTICHELPER_HPP
#define SEMANTICHELPER_HPP

#include <vector>
#include <string>

#include "Type.hpp"
#include "Symbol.hpp"

using namespace std;

namespace Meow
{

	class ErrorManager;
	class SymbolTable;
	class PalScanner;
	class Type;
	class Symbol;

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

	class SemanticHelper
	{
		public:
			SemanticHelper(PalScanner* scanner,
					ErrorManager* manager,
					SymbolTable* table);

			void addPredefinedSymbols();

			Symbol* getSymbol(string id, bool assertExists = true);
			ErrorManager* getErrorManager() { return m_errorManager; }

			void defineType(string id, Type* type);
			Type* getTypeForVarId(std::string id, bool& assignable, bool onLHS, vector<Symbol*>* functionStack);
			Type* getTypeFromID(string id);

			bool isOrdinalType(Type* t);
			bool isStringType(Type* t);
			Type* makeArrayType(Type* indexType, Type* elementType);
			Type* makeArrayType(ConstExpr start, ConstExpr end, Type* elementType);

			void declareVariable(string id, Type* type);

			ConstExpr getConstOpResult(Operator op, ConstExpr expr);
			ConstExpr getConstOpResult(Operator op, ConstExpr left, ConstExpr right);

			Type* getOpResultType(Operator op, Type* type);
			Type* getOpResultType(Operator op, Type* leftType, Type* rightType);

			bool checkCompatible(Type* ltype, Type* rtype);
			bool checkAssignmentCompatible(Type* ltype, Type* rtype);
			void checkBoolean(Type *);

			Type* checkFunctionInvocation(string functionName, 
							InvocationParameters* params);
			void checkProcedureInvocation(string procedureName, 
							InvocationParameters* params);
			void checkInvocationArgs(Symbol* fpSymbol, 
						InvocationParameters* params);

			Type* getRecordFieldType(Type* recordType, string fieldName, bool& assignable);
			Type* getSubscriptedArrayType(Type* arrayType, Type* subscriptType, bool& assignable);

			bool checkDuplicateField(IdTypePairList* fields, IdTypePair* field);

			Type* getBooleanType() { return &m_booleanType; }
			Type* getIntegerType() { return &m_integerType; }
			Type* getRealType() { return &m_realType; }
			Type* getCharType() { return &m_charType; }

			Symbol* getWrite() { return m_write; }
			Symbol* getWriteln() { return m_writeln; }

		private:

			PalScanner* m_scanner;
			SymbolTable* m_table;
			ErrorManager* m_errorManager;

			// Predefined simple types
			Type m_booleanType;
			Type m_integerType;
			Type m_realType;
			Type m_charType;

			// Predefined procedures + functions
			Symbol* m_succ;
			Symbol* m_pred;
			Symbol* m_ord;
			Symbol* m_abs;
			Symbol* m_sqr;

			Symbol* m_write;
			Symbol* m_writeln;

	};
}

#endif

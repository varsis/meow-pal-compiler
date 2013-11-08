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

	struct ConstExpr
	{
		Type* type;
		Value value;
	};

	class SemanticHelper
	{
		public:
			SemanticHelper(PalScanner* scanner,
					ErrorManager* manager,
					SymbolTable* table);

			void addPredefinedSymbols();

			Symbol* getSymbol(string id, bool assertExists = true);

			void defineType(string id, Type* type);
			Type* getTypeForVarId(string id);
			Type* getTypeFromID(string id);

			bool isOrdinalType(Type* t);
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

			void checkProcedureInvocation(string procedureName, 
							InvocationParameters* params);

			Type* getRecordFieldType(Type* recordType, string fieldName);
			Type* getSubscriptedArrayType(Type* arrayType, Type* subscriptType);

			Type* getBooleanType() { return &m_booleanType; }
			Type* getIntegerType() { return &m_integerType; }
			Type* getRealType() { return &m_realType; }
			Type* getCharType() { return &m_charType; }

		private:

			PalScanner* m_scanner;
			SymbolTable* m_table;
			ErrorManager* m_errorManager;

			// Predefined simple types
			Type m_booleanType;
			Type m_integerType;
			Type m_realType;
			Type m_charType;

	};
}

#endif

#include "SemanticHelper.hpp"
#include "ErrorManager.hpp"
#include "Scanner.hpp"
#include "SymbolTable.hpp"
#include "Type.hpp"

namespace Meow
{

	SemanticHelper::SemanticHelper(PalScanner* scanner,
					ErrorManager* manager,
					SymbolTable* table)
		: m_scanner(scanner)
		, m_table(table)
		, m_errorManager(manager)
	{
	}

	void SemanticHelper::addPredefinedSymbols()
	{
		// add predefined types

		Symbol* intSymbol = new Symbol("integer", Symbol::TypeSymbol);
		intSymbol->setType(getIntegerType());
		m_table->addSymbol(intSymbol);

		Symbol* realSymbol = new Symbol("real", Symbol::TypeSymbol);
		realSymbol->setType(getRealType());
		m_table->addSymbol(realSymbol);

		Symbol* charSymbol = new Symbol("char", Symbol::TypeSymbol);
		charSymbol->setType(getCharType());
		m_table->addSymbol(charSymbol);

		Symbol* boolSymbol = new Symbol("boolean", Symbol::TypeSymbol);
		boolSymbol->setType(getBooleanType());
		m_table->addSymbol(boolSymbol);

		// AT LEAST FOR NOW -- define a string type
		// TODO remove this if required
		Symbol* stringSymbol = new Symbol("string", Symbol::TypeSymbol);
		ConstExpr stringStart = {getIntegerType(), {1}};
		ConstExpr stringEnd = {getIntegerType(), {255}};
		Type* stringType = makeArrayType(stringStart, stringEnd, getCharType());
		stringSymbol->setType(stringType);
		m_table->addSymbol(stringSymbol);

		// add predefined constants
		Symbol* trueSymbol = new Symbol("true", Symbol::ConstantSymbol);
		trueSymbol->setType(getBooleanType());
		m_table->addSymbol(trueSymbol);

		Symbol* falseSymbol = new Symbol("false", Symbol::ConstantSymbol);
		falseSymbol->setType(getBooleanType());
		m_table->addSymbol(falseSymbol);
		
		// TODO max int value
		Symbol* maxintSymbol = new Symbol("maxint", Symbol::ConstantSymbol);
		maxintSymbol->setType(getIntegerType());
		// Max 32 bit word
		//maxintSymbol->setConstantValue(2^31);
		m_table->addSymbol(maxintSymbol);

		// PREDEFINED PROCEDURES
		
		Symbol* readSymbol = new Symbol("read", Symbol::ProcedureSymbol);
		readSymbol->setIOProc(true);
		m_table->addSymbol(readSymbol);
		
		Symbol* readlnSymbol = new Symbol("readln", Symbol::ProcedureSymbol);
		readlnSymbol->setIOProc(true);
		m_table->addSymbol(readlnSymbol);
		
		Symbol* writelnSymbol = new Symbol("writeln", Symbol::ProcedureSymbol);
		writelnSymbol->setIOProc(true);
		m_table->addSymbol(writelnSymbol);
		
		Symbol* writeSymbol = new Symbol("write", Symbol::ProcedureSymbol);
		writeSymbol->setIOProc(true);
		m_table->addSymbol(writeSymbol);
		
		// PREDEFINED FUNCTIONS

		Symbol* ordFunctionSymbol = new Symbol("ord", Symbol::FunctionSymbol);
		//TODO a Type?
		//ordFunctionSymbol->setType();
		m_table->addSymbol(ordFunctionSymbol);
		
		Symbol* chrFunctionSymbol = new Symbol("chr", Symbol::FunctionSymbol);
		//TODO a Type?
		//chrFunctionSymbol->setType();
		m_table->addSymbol(chrFunctionSymbol);
		
		Symbol* truncFunctionSymbol = new Symbol("trunc", Symbol::FunctionSymbol);
		//TODO a Type?
		//truncFunctionSymbol->setType();
		m_table->addSymbol(truncFunctionSymbol);
		
		Symbol* roundFunctionSymbol = new Symbol("round", Symbol::FunctionSymbol);
		//TODO a Type?
		//roundFunctionSymbol->setType();
		m_table->addSymbol(roundFunctionSymbol);
		
		Symbol* succFunctionSymbol = new Symbol("succ", Symbol::FunctionSymbol);
		//TODO a Type?
		//succFunctionSymbol->setType();
		m_table->addSymbol(succFunctionSymbol);
		
		Symbol* predFunctionSymbol = new Symbol("pred", Symbol::FunctionSymbol);
		//TODO a Type?
		//predFunctionSymbol->setType();
		m_table->addSymbol(predFunctionSymbol);
		
		Symbol* oddFunctionSymbol = new Symbol("odd", Symbol::FunctionSymbol);
		//TODO a Type?
		//oddFunctionSymbol->setType();
		m_table->addSymbol(oddFunctionSymbol);
		
		Symbol* absFunctionSymbol = new Symbol("abs", Symbol::FunctionSymbol);
		//TODO a Type?
		//absFunctionSymbol->setType();
		m_table->addSymbol(absFunctionSymbol);
		
		Symbol* sqrFunctionSymbol = new Symbol("sqr", Symbol::FunctionSymbol);
		//TODO a Type?
		//sqrFunctionSymbol->setType();
		m_table->addSymbol(sqrFunctionSymbol);
		
		Symbol* sqrtFunctionSymbol = new Symbol("sqrt", Symbol::FunctionSymbol);
		//TODO a Type?
		//sqrtFunctionSymbol->setType();
		m_table->addSymbol(sqrtFunctionSymbol);

		Symbol* sinFunctionSymbol = new Symbol("sin", Symbol::FunctionSymbol);
		//TODO a Type?
		//sinFunctionSymbol->setType();
		m_table->addSymbol(sinFunctionSymbol);
		
		Symbol* expFunctionSymbol = new Symbol("exp", Symbol::FunctionSymbol);
		//TODO a Type?
		//expFunctionSymbol->setType();
		m_table->addSymbol(expFunctionSymbol);
		
		Symbol* lnFunctionSymbol = new Symbol("ln", Symbol::FunctionSymbol);
		//TODO a Type?
		//lnFunctionSymbol->setType();
		m_table->addSymbol(lnFunctionSymbol);

	}

	Symbol* SemanticHelper::getSymbol(string id, bool assertExists)
	{
		Symbol* symbol = m_table->getSymbol(id);

		if (assertExists && !symbol) {
			m_errorManager->addError(new Error(SemanticError,
				"Undefined identifier",
				m_scanner->lineno()));
		}

		return symbol;
	}

	void SemanticHelper::defineType(string id, Type* type)
	{
		Symbol* typeSymbol = m_table->getSymbolCurLevel(id);

		if (typeSymbol)
		{
			m_errorManager->addError(new Error(IdentifierInUse,
				"Identifier was already declared at current lexical level.",
				m_scanner->lineno()));
		}

		typeSymbol = new Symbol(id, Symbol::TypeSymbol);

		typeSymbol->setType(type);

		m_table->addSymbol(typeSymbol);
	}

	Type* SemanticHelper::getTypeForVarId(std::string id)
	{
		Symbol* symbol = m_table->getSymbol(id);

		if (!symbol)
		{
			m_errorManager->addError(
					new Error(SemanticError, // TODO
						"Identifier is not defined.",
						m_scanner->lineno()));

		}
		else
		{
			return symbol->getType();
		}

		// just return an int by default??
		return getIntegerType();
	}

	// rename to typeId?
	Type* SemanticHelper::getTypeFromID(std::string id)
	{
		Symbol* typeSymbol = m_table->getSymbol(id);

		if (!typeSymbol)
		{
			m_errorManager->addError(
					new Error(SemanticError, // TODO
						"Type is not defined.",
						m_scanner->lineno()));

		}
		else if (typeSymbol->getSymbolType() != Symbol::TypeSymbol)
		{
			m_errorManager->addError(
					new Error(SemanticError, // TODO
						"Identifier is not a type.",
						m_scanner->lineno()));
		}
		else
		{
			return typeSymbol->getType();
		}

		// just return a raw int by default??
		return getIntegerType();
	}

	bool SemanticHelper::isOrdinalType(Type* t)
	{
		// if it's one of the base ordinal types
		if (t == getIntegerType() 
				|| t == getBooleanType()
				|| t == getCharType())
		{
			return true;
		}

		if (t->getTypeClass() == Type::EnumeratedType)
		{
			return true;
		}

		return false;
	}

	Type* SemanticHelper::makeArrayType(Type* indexType, Type* elementType)
	{
		if (!isOrdinalType(indexType))
		{
			// TODO error
			return NULL;
		}

		ArrayIndexRange range;
		range.start = indexType->getMinValue().int_val;
		range.end = indexType->getMaxValue().int_val;

		return new Type(elementType, indexType, range);
	}

	Type* SemanticHelper::makeArrayType(ConstExpr start, ConstExpr end, Type* elementType)
	{
		// the start and end types need to be compatible (equal?)
		if (!checkCompatible(start.type, end.type))
		{
			// TODO error
			return NULL;
		}

		// the start and end types need to be ordinal
		if (!isOrdinalType(start.type) || !isOrdinalType(end.type))
		{
			// TODO error
			return NULL;
		}
	
		Type* indexType = start.type; // TODO assume or assert types are equal?

		// Check that start doesn't come after end
		//if (indexType->getTypeClass() == Type::EnumeratedType)
		//{
			// check start.value doesn't come after end.value
			// TODO values can be enums!!! fack!!
			// hey -- but we can just treat enums like ints though right?
		//}
		//else if (start.value.int_val > end.value.int_val)
		if (start.value.int_val > end.value.int_val)
		{
			// TODO error
			return NULL;
		}

		ArrayIndexRange range;

		//if (start.type->getTypeClass() == Type::EnumeratedType)
		//{
			//range.start = start.value.enum_val
			//range.end = end.value.enum_val
		//}
		//else
		{
			range.start = start.value.int_val;
			range.end = end.value.int_val;
		}

		return new Type(elementType, indexType, range);
	}

	void SemanticHelper::declareVariable(string id, Type* type)
	{
		Symbol* sym = m_table->getSymbolCurLevel(id);

		if (sym)
		{
			m_errorManager->addError(new Error(IdentifierInUse,
				"Identifier was already declared at current lexical level.",
				m_scanner->lineno()));
		}

		sym = new Symbol(id, Symbol::VariableSymbol);
		sym->setType(type);
		m_table->addSymbol(sym);
	}

	// unary operators
	ConstExpr SemanticHelper::getConstOpResult(Operator op, ConstExpr expr)
	{
		ConstExpr result;
		result.type = getIntegerType();
		result.value.int_val = 0;

		switch (op)
		{
			case OpPLUS:
				if (expr.type == getRealType())
				{
					result.value.real_val = expr.value.real_val;
					result.type = expr.type;
				}
				else
				{
					result.value.int_val = expr.value.int_val;
					result.type = expr.type;
				}
				break;

			case OpMINUS:
				if (expr.type == getRealType())
				{
					result.value.real_val = -expr.value.real_val;
					result.type = expr.type;
				}
				else
				{
					result.value.int_val = -expr.value.int_val;
					result.type = expr.type;
				}
				break;

			case OpNOT:
				if (expr.type == getRealType())
				{
					result.value.int_val = !((bool)expr.value.real_val);
				}
				else
				{
					result.value.int_val = !((bool)expr.value.int_val);
				}
				result.type = getBooleanType();
				break;

			default:
				break;
		}

		return result;
	}


	ConstExpr SemanticHelper::getConstOpResult(Operator op, ConstExpr left, ConstExpr right)
	{
		ConstExpr result;
		result.type = getIntegerType();
		result.value.int_val = 0;

		double leftValuef = (left.type == getRealType()) ? left.value.real_val : left.value.int_val;
		double rightValuef = (right.type == getRealType()) ? right.value.real_val : right.value.int_val;

		int leftValuei = (left.type == getRealType()) ? left.value.real_val : left.value.int_val;
		int rightValuei = (right.type == getRealType()) ? right.value.real_val : right.value.int_val;

		switch (op)
		{
			// comparison ops
			case OpEQ:
				result.value.int_val = leftValuef == rightValuef;
				result.type = getBooleanType();
				break;
			case OpNE:
				result.value.int_val = leftValuef != rightValuef;
				result.type = getBooleanType();
				break;
			case OpLE:
				result.value.int_val = leftValuef <= rightValuef;
				result.type = getBooleanType();
				break;
			case OpLT:
				result.value.int_val = leftValuef <= rightValuef;
				result.type = getBooleanType();
				break;
			case OpGE:
				result.value.int_val = leftValuef >= rightValuef;
				result.type = getBooleanType();
				break;
			case OpGT:
				result.value.int_val = leftValuef > rightValuef;
				result.type = getBooleanType();
				break;

			// arithmetic ops
			case OpADD:
				// if one is real...
				if (left.type == getRealType() || right.type == getRealType())
				{
					result.type = getRealType();
					result.value.real_val = leftValuef + rightValuef;
				}
				else
				{
					result.type = getIntegerType();
					result.value.int_val = leftValuei + rightValuei;
				}
				break;
			case OpSUBTRACT:
				// if one is real...
				if (left.type == getRealType() || right.type == getRealType())
				{
					result.type = getRealType();
					result.value.real_val = leftValuef - rightValuef;
				}
				else
				{
					result.type = getIntegerType();
					result.value.int_val = leftValuei - rightValuei;
				}
				break;
			case OpMULTIPLY:
				// if one is real...
				if (left.type == getRealType() || right.type == getRealType())
				{
					result.type = getRealType();
					result.value.real_val = leftValuef * rightValuef;
				}
				else
				{
					result.type = getIntegerType();
					result.value.int_val = leftValuei * rightValuei;
				}
				break;

			case OpREALDIVIDE:
				result.type = getRealType();
				result.value.real_val = leftValuef / rightValuef;
				break;

			case OpINTDIVIDE:
				result.type = getIntegerType();
				result.value.real_val = leftValuei / rightValuei;
				break;

			case OpMOD:
				result.type = getIntegerType();
				result.value.real_val = leftValuei % rightValuei;
				break;

			// logical ops
			case OpOR:
				result.type = getIntegerType();
				result.value.int_val = leftValuef || rightValuef;
				break;

			case OpAND:
				result.type = getIntegerType();
				result.value.int_val = leftValuef && rightValuef;
				break;

			default:
				break;

		}

		return result;
	}

	// unary operators
	Type* SemanticHelper::getOpResultType(Operator op, Type* type)
	{
		switch (op)
		{
			case OpPLUS:
				if (type == getRealType() || type == getIntegerType())
				{
					return type;
				}
				break;

			case OpMINUS:
				if (type == getRealType() || type == getIntegerType())
				{
					return type;
				}
				break;

			case OpNOT:
				if (type == getBooleanType())
				{
					return type;
				}

				break;

			default:
				break;
		}

		return NULL;
	}


	Type* SemanticHelper::getOpResultType(Operator op, Type* leftType, Type* rightType)
	{

		// TODO what ops do record types support? anything?

		switch (op)
		{
			// comparison ops
			case OpEQ:
			case OpNE:
			case OpLE:
			case OpLT:
			case OpGE:
			case OpGT:
				if (checkCompatible(leftType, rightType))
				{
					// TODO are these ALL defined for bools?
					return getBooleanType();
				}
				break;

			// arithmetic ops
			case OpADD:
			case OpSUBTRACT:
			case OpMULTIPLY:
				if (checkCompatible(leftType, rightType))
				{
					// if their types are integer or real
					if ((leftType == getIntegerType()
						|| leftType == getRealType())
						&&(rightType == getIntegerType()
						|| rightType == getRealType()))
					{
						// result is real if one operand is real
						if (leftType == getRealType() 
						|| rightType == getRealType())
						{
							return getRealType();
						}

						// otherwsie result is same type
						return leftType;
					}
				}
				break;

			case OpREALDIVIDE:
				if (checkCompatible(leftType, rightType))
				{
					// if their types are integer or real
					if ((leftType == getIntegerType()
						|| leftType == getRealType())
						&&(rightType == getIntegerType()
						|| rightType == getRealType()))
					{
						return getRealType(); // the predefined real type
					}
				}
				break;

			case OpINTDIVIDE:
				if (checkCompatible(leftType, rightType))
				{
					if (leftType == getIntegerType()
						&& rightType == getIntegerType())
					{
						return getIntegerType();
					}
				}
				break;

			case OpMOD:
				if (checkCompatible(leftType, rightType))
				{
					if (leftType == getIntegerType()
						&& rightType == getIntegerType())
					{
						return getIntegerType();
					}
				}
				break;

			// logical ops
			case OpOR:
			case OpAND:
				if (checkCompatible(leftType, rightType))
				{
					if (leftType == getBooleanType()
						&& rightType == getBooleanType())
					{
						return getBooleanType();
					}
				}
				break;

			default:
				break;

		}

		// if not compatible, return null
		return NULL;
	}

	bool SemanticHelper::checkCompatible(Type* ltype, Type* rtype)
	{
		if (ltype == NULL || rtype == NULL)
		{
			return false;
		}

		// see section on types in pal reference

		// compatible if they are the exact same type
		if (ltype == rtype)
		{
			return true;
		}

		// strings of the same size are compatible
		if (ltype->getTypeClass() == Type::ArrayType && rtype->getTypeClass() == Type::ArrayType)
		{
			if (ltype->getElementType() == getCharType() 
					&& rtype->getElementType() == getCharType())
			{
				// TODO
				// both types need array index starting at one
				// array index ends much match
			}
		}

		// compatable if types are the predefined integer / real types
		if ((ltype == getIntegerType() || ltype == getRealType())
			&& (rtype == getIntegerType() || rtype == getRealType()))
		{
			return  true;
		}

		// otherwise, incompatible!
		return false;
	}

	bool SemanticHelper::checkAssignmentCompatible(Type* ltype, Type* rtype)
	{
		if (ltype == NULL || rtype == NULL)
		{
			return false;
		}

		// Check string compatiblilty
		if (ltype->getTypeClass() == Type::ArrayType)
		{
			// string are any char arrays with integer index starting at 1;
			if (ltype->getElementType() == getCharType() 
					&& ltype->getIndexType() == getIntegerType()
					&& ltype->getIndexRange().start == 1)
			{
				// if we are assigning a string literal, assume its ok
				if (rtype->getTypeClass() == Type::StringLiteralType)
				{
					return true;
				}

				// if we are assigning a char array, must have same indices
				if ( rtype->getElementType() == getCharType()
					&& rtype->getIndexType() == getIntegerType()
					&& rtype->getIndexRange().start == 1
					&& ltype->getIndexRange().end == rtype->getIndexRange().end)
				{
					return true;
				}


				// TODO better error
				m_errorManager->addError(new Error(SemanticError,
						"Assigning string with invalid type", 
						m_scanner->lineno()));
			}
		}

		// if rtype is a string literal with length 1, treat it as a char
		if (rtype->getTypeClass() == Type::StringLiteralType)
		{
			if (rtype->getStringLiteral().size() == 1)
			{
				rtype = getCharType();
			}
		}

		if (ltype == getRealType() && rtype == getIntegerType())
		{
			return true;
		}

		if (ltype == rtype)
		{
			return true;
		}
		
		return false;
	}
	
	void SemanticHelper::checkBoolean(Type * t)
	{	
		if (t != getBooleanType())
		{
			m_errorManager->addError(new Error(InvalidExpression,
					"Non-Boolean While/If clause.", 
					m_scanner->lineno()));
		}
	}

	Type* SemanticHelper::getRecordFieldType(Type* recordType, string fieldName)
	{
		Type* fieldType = NULL;

		if (recordType == NULL)
		{
			// TODO error, or just ignore?
		}
		else if (recordType->getTypeClass() != Type::RecordType)
		{
			// TODO ERROR type is not a record
			m_errorManager->addError(new Error(SemanticError,
					"Accessing field on type that is not a record", 
					m_scanner->lineno()));
		}
		else
		{
			IdTypePairList* fields = recordType->getFields();

			if (fields == NULL)
			{
				// ERROR - record type has no fields?
				m_errorManager->addError(new Error(SemanticError,
						"Record has no fields", 
						m_scanner->lineno()));
			}
			else
			{
				// get record field corresponding to name
				IdTypePairList::iterator it;
				for (it = fields->begin(); it != fields->end(); ++it)
				{
					if ((*it)->first->compare(fieldName) == 0)
					{
						fieldType = (*it)->second;
					}
				}
			}

			if (fieldType == NULL)
			{
				// TODO ERROR - invalid field for record!
				m_errorManager->addError(new Error(SemanticError,
						"No matchin field in record",
						m_scanner->lineno()));
			}
		}

		return fieldType;
	}

	Type* SemanticHelper::getSubscriptedArrayType(Type* arrayType, Type* subscriptType)
	{
		Type* result = NULL;

		if (arrayType == NULL)
		{
			// TODO error or just ignore and return null?
		}
		else if (arrayType->getTypeClass() != Type::ArrayType)
		{
			// TODO ERROR type is not an array
			m_errorManager->addError(new Error(SemanticError,
					"Subscripted variable is not an array",
					m_scanner->lineno()));
		}
		else
		{
			// check subscript type matches index type (or is at least assignment compatible?)
			if (!checkAssignmentCompatible(arrayType->getIndexType(), subscriptType))
			{
				m_errorManager->addError(new Error(SemanticError,
						"Subscript is not compatible with array index type",
						m_scanner->lineno()));
			}
			else
			{
				result = arrayType->getElementType();
			}
		}
		return result;
	}
}

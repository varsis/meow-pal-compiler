#include "SemanticHelper.hpp"
#include "ErrorManager.hpp"
#include "Scanner.hpp"
#include "SymbolTable.hpp"
#include "Type.hpp"

namespace Meow
{

	SemanticHelper::SemanticHelper(PalScanner* scanner,
					ErrorManager* manager,
					SymbolTable* table,
					bool languageExtensions)
		: m_scanner(scanner)
		, m_table(table)
		, m_errorManager(manager)
		, m_languageExtensions(languageExtensions)
	{
		addPredefinedSymbols();
	}

	void SemanticHelper::addPredefinedSymbols()
	{
		// add predefined types

		Symbol* intSymbol = new Symbol("integer", Symbol::TypeSymbol);
		getIntegerType()->setMaxIntValue(2147483647);
		getIntegerType()->setMinIntValue(-2147483647);
		intSymbol->setType(getIntegerType());
		m_table->addSymbol(intSymbol);

		Symbol* realSymbol = new Symbol("real", Symbol::TypeSymbol);
		realSymbol->setType(getRealType());
		m_table->addSymbol(realSymbol);

		Symbol* charSymbol = new Symbol("char", Symbol::TypeSymbol);
		charSymbol->setType(getCharType());
		getCharType()->setMaxIntValue(255);
		getCharType()->setMinIntValue(0);
		m_table->addSymbol(charSymbol);

		Symbol* boolSymbol = new Symbol("boolean", Symbol::TypeSymbol);
		boolSymbol->setType(getBooleanType());
		getBooleanType()->setMaxIntValue(1);
		getBooleanType()->setMinIntValue(0);
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
		trueSymbol->setConstantValue(1);
		m_table->addSymbol(trueSymbol);

		Symbol* falseSymbol = new Symbol("false", Symbol::ConstantSymbol);
		falseSymbol->setType(getBooleanType());
		falseSymbol->setConstantValue(0);
		m_table->addSymbol(falseSymbol);
		
		Symbol* maxintSymbol = new Symbol("maxint", Symbol::ConstantSymbol);
		maxintSymbol->setType(getIntegerType());
		maxintSymbol->setConstantValue(2147483647);
		m_table->addSymbol(maxintSymbol);

		Symbol* minintSymbol = new Symbol("minint", Symbol::ConstantSymbol);
		minintSymbol->setType(getIntegerType());
		minintSymbol->setConstantValue(-2147483647);
		m_table->addSymbol(minintSymbol);

		// PREDEFINED PROCEDURES
		
		m_read = new Symbol("read", Symbol::ProcedureSymbol);
		m_read->setProcClass(BuiltInInput);
		m_table->addSymbol(m_read);
		
		m_readln = new Symbol("readln", Symbol::ProcedureSymbol);
		m_readln->setProcClass(BuiltInInput);
		m_table->addSymbol(m_readln);
		
		
		m_writeln = new Symbol("writeln", Symbol::ProcedureSymbol);
		m_writeln->setProcClass(BuiltInOutput);
		m_table->addSymbol(m_writeln);
		
		m_write = new Symbol("write", Symbol::ProcedureSymbol);
		m_write->setProcClass(BuiltInOutput);
		m_table->addSymbol(m_write);
		
		// PREDEFINED FUNCTIONS

		Symbol* ordFunctionSymbol = new Symbol("ord", Symbol::FunctionSymbol);
		m_ord = ordFunctionSymbol;
		ordFunctionSymbol->setType(getIntegerType());
		m_table->addSymbol(ordFunctionSymbol);
	
		Symbol* chrFunctionSymbol = new Symbol("chr", Symbol::FunctionSymbol);
		chrFunctionSymbol->setType(getCharType());
		chrFunctionSymbol->addParameter("", getIntegerType());
		m_table->addSymbol(chrFunctionSymbol);
		
		Symbol* truncFunctionSymbol = new Symbol("trunc", Symbol::FunctionSymbol);
		truncFunctionSymbol->setType(getIntegerType());
		truncFunctionSymbol->addParameter("", getRealType());
		m_table->addSymbol(truncFunctionSymbol);
		
		Symbol* roundFunctionSymbol = new Symbol("round", Symbol::FunctionSymbol);
		roundFunctionSymbol->setType(getIntegerType());
		roundFunctionSymbol->addParameter("", getRealType());
		m_table->addSymbol(roundFunctionSymbol);
		
		Symbol* succFunctionSymbol = new Symbol("succ", Symbol::FunctionSymbol);
		m_succ = succFunctionSymbol;
		m_table->addSymbol(succFunctionSymbol);
		
		Symbol* predFunctionSymbol = new Symbol("pred", Symbol::FunctionSymbol);
		m_pred = predFunctionSymbol;
		m_table->addSymbol(predFunctionSymbol);
		
		Symbol* oddFunctionSymbol = new Symbol("odd", Symbol::FunctionSymbol);
		oddFunctionSymbol->setType(getBooleanType());
		oddFunctionSymbol->addParameter("", getIntegerType());
		m_table->addSymbol(oddFunctionSymbol);
		
		Symbol* absFunctionSymbol = new Symbol("abs", Symbol::FunctionSymbol);
		m_abs = absFunctionSymbol; // Save the symbol addr in case of redef
		absFunctionSymbol->addParameter("", getRealType());
		m_table->addSymbol(absFunctionSymbol);
		
		Symbol* sqrFunctionSymbol = new Symbol("sqr", Symbol::FunctionSymbol);
		m_sqr = sqrFunctionSymbol; // Save the symbol addr in case of redef
		sqrFunctionSymbol->addParameter("", getRealType());
		m_table->addSymbol(sqrFunctionSymbol);
		
		Symbol* sqrtFunctionSymbol = new Symbol("sqrt", Symbol::FunctionSymbol);
		sqrtFunctionSymbol->setType(getRealType());
		sqrtFunctionSymbol->addParameter("", getRealType());
		m_table->addSymbol(sqrtFunctionSymbol);

		Symbol* sinFunctionSymbol = new Symbol("sin", Symbol::FunctionSymbol);
		sinFunctionSymbol->setType(getRealType());
		sinFunctionSymbol->addParameter("", getRealType());
		m_table->addSymbol(sinFunctionSymbol);
		
		Symbol* expFunctionSymbol = new Symbol("exp", Symbol::FunctionSymbol);
		expFunctionSymbol->setType(getRealType());
		expFunctionSymbol->addParameter("", getRealType());
		m_table->addSymbol(expFunctionSymbol);
		
		Symbol* lnFunctionSymbol = new Symbol("ln", Symbol::FunctionSymbol);
		lnFunctionSymbol->setType(getRealType());
		lnFunctionSymbol->addParameter("", getRealType());
		m_table->addSymbol(lnFunctionSymbol);

		// Make sure that builtins can be redefed
		m_table->incLevel();

	}

	Symbol* SemanticHelper::getSymbol(string id, bool assertExists)
	{
		Symbol* symbol = m_table->getSymbol(id);

		if (assertExists && !symbol) {
			m_errorManager->addError(new Error(SemanticError,
				"Undefined identifier, '" + id + "'.",
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
				"Identifier, '" + id + "', was already declared at current lexical level.",
				m_scanner->lineno()));
		}

		typeSymbol = new Symbol(id, Symbol::TypeSymbol);

		typeSymbol->setType(type);

		m_table->addSymbol(typeSymbol);
	}

	Type* SemanticHelper::getTypeForVarId(std::string id, bool& assignable, bool onLHS, vector<Symbol*>* functionStack)
	{
		Symbol* symbol = m_table->getSymbol(id);

		assignable = false;

		if (!symbol)
		{
			m_errorManager->addError(
					new Error(SemanticError,
						"Identifier, '" + id + "' is not defined.",
						m_scanner->lineno()));

		}
		else
		{
			// Name is assignable only if it's a variable
			assignable = symbol->getSymbolType() == Symbol::VariableSymbol;

			// throw error if name is a procedure
			if (symbol->getSymbolType() == Symbol::ProcedureSymbol)
			{
				m_errorManager->addError(
						new Error(SemanticError,
							"Invalid reference to procedure, '" + id + "'.",
							m_scanner->lineno()));
			}

			// throw error if name is a type symbol
			if (symbol->getSymbolType() == Symbol::TypeSymbol)
			{
				m_errorManager->addError(
						new Error(SemanticError,
							"Invalid use of type identifier.",
							m_scanner->lineno()));
			}

			if (symbol->getSymbolType() == Symbol::FunctionSymbol)
			{

				bool isEnclosingFunction = false;

				vector<Symbol*>::iterator it;
				for (it = functionStack->begin(); it != functionStack->end(); ++it)
				{
					if ((*it)->getSymbolType() == Symbol::FunctionSymbol
						&& (*it) == symbol)
					{
						isEnclosingFunction = true;
						break;
					}
				}

				if (onLHS && isEnclosingFunction)
				{
					// can assign to an enclosing function name as return value
					assignable = true;
				}
				else
				{
					m_errorManager->addError(
							new Error(SemanticError,
								"Invalid reference to function, '" + id + "'.",
								m_scanner->lineno()));
				}
			}

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
					new Error(SemanticError,
						"Type, '" + id + "', is not defined.",
						m_scanner->lineno()));

		}
		else if (typeSymbol->getSymbolType() != Symbol::TypeSymbol)
		{
			m_errorManager->addError(
					new Error(SemanticError, 
						"'" + id + "' is not a type.",
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

	bool SemanticHelper::isStringType(Type* t)
	{
		return	t->getTypeClass() == Type::ArrayType
			&& t->getElementType() == getCharType()
			&& t->getIndexType() == getIntegerType()
			&& t->getIndexRange().start == 1
			&& t->getIndexRange().end > 1;
	}

	Type* SemanticHelper::makeArrayType(Type* indexType, Type* elementType)
	{
		if (!isOrdinalType(indexType))
		{
			m_errorManager->addError(new Error(
					SemanticError,
					"Indices must be ordinal types; boolean, enum, or integer.",
					m_scanner->lineno()));
			return NULL;
		}

		ArrayIndexRange range;
		range.start = indexType->getMinValue().int_val;
		range.end = indexType->getMaxValue().int_val;

		return new Type(elementType, indexType, range);
	}

	Type* SemanticHelper::makeArrayType(ConstExpr start, ConstExpr end, Type* elementType)
	{
		ArrayIndexRange range;
		range.start = start.value.int_val;
		range.end = end.value.int_val;

		// the start and end types need to be compatible (equal?)
		if (start.type != end.type || start.type == NULL || end.type == NULL)
		{
			m_errorManager->addError(new Error(
					SemanticError,
					"Indices must be same type.",
					m_scanner->lineno()));

			return new Type(elementType, NULL, range);
		}

		Type* indexType = start.type;

		// the start and end types need to be ordinal
		if (!isOrdinalType(start.type) || !isOrdinalType(end.type))
		{
			m_errorManager->addError(new Error(
					SemanticError,
					"Indices must be ordinal types; boolean, enum, or integer.",
					m_scanner->lineno()));
			return new Type(elementType, NULL, range);
		}
	
		// Check that start doesn't come after end
		if (start.value.int_val > end.value.int_val)
		{
			m_errorManager->addError(new Error(SemanticError,
				"Array start index is greater than end index",
				m_scanner->lineno()));
		}


		return new Type(elementType, indexType, range);
	}

	void SemanticHelper::declareVariable(string id, Type* type)
	{
		Symbol* sym = m_table->getSymbolCurLevel(id);

		if (sym)
		{
			m_errorManager->addError(new Error(IdentifierInUse,
				"Identifier, '" + id + "', was already declared at current lexical level.",
				m_scanner->lineno()));
		}

		sym = new Symbol(id, Symbol::VariableSymbol);
		sym->setType(type);
		m_table->addSymbol(sym);
		m_table->allocateSpace(sym, type);
	}
	
	void SemanticHelper::declareParameter(Symbol* param)
	{
		Symbol* sym = m_table->getSymbolCurLevel(param->getName());

		if (sym)
		{
			m_errorManager->addError(new Error(IdentifierInUse,
				"Identifier, '" + param->getName() + "', was already declared at current lexical level.",
				m_scanner->lineno()));
		}

		m_table->addSymbol(param);
	}

	Symbol* SemanticHelper::declareRoutine(string label, string* id, ParameterList* parameters, string* returnId)
	{
		Symbol* routineSym = m_table->getSymbolCurLevel(*id);
		Type * returnType = NULL;
		int offset;

		if (routineSym)
		{
			m_errorManager->addError(new Error(IdentifierInUse,
							"Identifier, '" + *id + "', was already declared at current lexical level.",
							m_scanner->lineno()));
		}

		if (returnId == NULL)
		{
			routineSym = new Symbol(*id, Symbol::ProcedureSymbol);
		}
		else
		{
			routineSym = new Symbol(*id, Symbol::FunctionSymbol);
			returnType = getTypeFromID(*returnId);
			routineSym->setType(returnType);
			routineSym->setLocation(-(2 + returnType->getTypeSize()));
		}

		offset = 0;
		for (size_t i = 0; i < parameters->size(); i++)
		{
			if (parameters->at(i).var)
			{
				routineSym->allocParameterSpace(1);// just an address
			}
			else
			{
				routineSym->allocParameterSpace(parameters->at(i).type->getTypeSize());
			}
		}
		for (size_t i = 0; i < parameters->size(); i++)
		{
			routineSym->addParameter(parameters->at(i).id, parameters->at(i).type,
								parameters->at(i).var, offset);
			offset += parameters->at(i).type->getTypeSize();
			if (parameters->at(i).var)
			{
				offset += 1; // just an address
			}
			else
			{
				offset += parameters->at(i).type->getTypeSize();
			}
		}

		routineSym->setLabel(label);

		m_table->addSymbol(routineSym);
		m_table->incLevel();

		// Now, make symbol that exists in method body's lexical level (for setting return value)
		// and declare parameters at that level
		
		if (returnId == NULL)
		{
			routineSym = new Symbol(*id, Symbol::ProcedureSymbol);
		}
		else
		{
			routineSym = new Symbol(*id, Symbol::FunctionSymbol);
			routineSym->setType(returnType);
			routineSym->setLocation(-(2 + returnType->getTypeSize()));
		}
		
		routineSym->setRecursive(true);

		offset = 0;
		for (size_t i = 0; i < parameters->size(); i++)
		{
			if (parameters->at(i).var)
			{
				routineSym->allocParameterSpace(1);// just an address
			}
			else
			{
				routineSym->allocParameterSpace(parameters->at(i).type->getTypeSize());
			}
		}
		for (size_t i = 0; i < parameters->size(); i++)
		{
			Symbol* param = routineSym->addParameter(parameters->at(i).id, parameters->at(i).type,
									parameters->at(i).var, offset);

			declareParameter(param);
			if (parameters->at(i).var)
			{
				offset += 1; // just an address
			}
			else
			{
				offset += parameters->at(i).type->getTypeSize();
			}
		}

		routineSym->setLabel(label);

		m_table->addSymbol(routineSym);

		return routineSym;
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
				if (rightValuef == 0)
				{
					m_errorManager->addError(new Error(InvalidExpression,
						"Division by zero.",
						m_scanner->lineno()));
					result.value.real_val = 0;
				}
				else
				{
					result.value.real_val = leftValuef / rightValuef;
				}
				break;

			case OpINTDIVIDE:
				result.type = getIntegerType();
				if (rightValuei == 0)
				{
					m_errorManager->addError(new Error(InvalidExpression,
						"Division by zero.",
						m_scanner->lineno()));
					result.value.real_val = 0;
				}
				else
				{
					result.value.real_val = leftValuei / rightValuei;
				}
				break;

			case OpMOD:
				result.type = getIntegerType();
				if (rightValuei == 0)
				{
					m_errorManager->addError(new Error(InvalidExpression,
						"Division by zero.",
						m_scanner->lineno()));
					result.value.real_val = 0;
				}
				else
				{
					result.value.real_val = leftValuei % rightValuei;
				}
				break;

			// logical ops
			case OpOR:
				result.type = getBooleanType();
				result.value.int_val = leftValuef || rightValuef;
				break;

			case OpAND:
				result.type = getBooleanType();
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
		switch (op)
		{
			// comparison ops
			case OpEQ:
			case OpNE:
			case OpLE:
			case OpLT:
			case OpGE:
			case OpGT:
				// must be compatible
				if (checkCompatible(leftType, rightType))
				{
					if ((leftType->getTypeClass() == Type::ArrayType && !isStringType(leftType))
						|| (rightType->getTypeClass() == Type::ArrayType && !isStringType(rightType))
						|| (rightType->getTypeClass() == Type::RecordType)
						|| (leftType->getTypeClass() == Type::RecordType))
					{
						// if they are arrays (but not strings)
						// or if they are record types, not valid!
						return NULL;
					}
					else
					{
						return getBooleanType();
					}
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

		// strings of the same size are compatible
		if (ltype->getTypeClass() == Type::ArrayType && rtype->getTypeClass() == Type::ArrayType)
		{
			if (ltype->getElementType() == getCharType() 
					&& rtype->getElementType() == getCharType())
			{
				// if we are comparing 'string' types, must have same indices (starting at 1)
				if (ltype->getIndexType() == getIntegerType()
					&& ltype->getIndexRange().start == 1
					&& rtype->getIndexType() == getIntegerType()
					&& rtype->getIndexRange().start == 1
					&& ltype->getIndexRange().end == rtype->getIndexRange().end)
				{
					return true;
				}
			}
		}

		// compatable if types are the predefined integer / real types
		if ((ltype == getIntegerType() || ltype == getRealType())
			&& (rtype == getIntegerType() || rtype == getRealType()))
		{
			return  true;
		}

		// if rtype is a string literal with length 1, treat it as a char
		if (rtype->getTypeClass() == Type::StringLiteralType)
		{
			if (rtype->getStringLiteral().size() == 1)
			{
				rtype = getCharType();
			}
		}

		// compatible if they are the exact same type
		if (ltype == rtype)
		{
			return true;
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
				if ( rtype->getTypeClass() == Type::ArrayType
					&& rtype->getElementType() == getCharType()
					&& rtype->getIndexType() == getIntegerType()
					&& rtype->getIndexRange().start == 1
					&& ltype->getIndexRange().end == rtype->getIndexRange().end)
				{
					return true;
				}
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

	Type* SemanticHelper::checkFunctionInvocation(string functionName, 
							InvocationParameters* params)
	{	
		Symbol* functionSymbol = m_table->getSymbol(functionName);
		if (!functionSymbol)
		{
			m_errorManager->addError(new Error(SemanticError,
							"Function '" + functionName + "' has not been declared.",
							m_scanner->lineno()));

		}
		else if (functionSymbol->getSymbolType() != Symbol::FunctionSymbol)
		{
			m_errorManager->addError(new Error(SemanticError,
							"'" + functionName + "' is not a function.",
							m_scanner->lineno()));
		}
		else
		{
			// check arguments
			if (functionSymbol == m_succ || functionSymbol == m_pred
				|| functionSymbol == m_ord)
			{
				if (params && params->size() != 1)
				{	
					m_errorManager->addError(new Error(
						SemanticError,
						"Expecting 1 argument for '" + functionName + "'.",
						m_scanner->lineno()));
				}
				else if (params && !isOrdinalType(params->at(0).type))
				{
					m_errorManager->addError(new Error(
						SemanticError,
						"Non-compatible parameter type for '" + functionName + "'; must be ordinal type (integer, boolean, char, or enum).",
						m_scanner->lineno()));
				}
			
			}
			else 
			{
				checkInvocationArgs(functionSymbol, params);
			}

			// get function return type
			if (functionSymbol == m_abs || functionSymbol == m_sqr
				|| functionSymbol == m_succ || functionSymbol == m_pred)
			{
				if (params && params->size() > 0u)
				{
					return params->at(0).type;
				}

			}

			return functionSymbol->getType();
		}

		return NULL;  // TODO or int?
	}

	void SemanticHelper::checkProcedureInvocation(string procedureName, 
							InvocationParameters* params)
	{	
		Symbol* procedureSymbol = m_table->getSymbol(procedureName);
		if (!procedureSymbol)
		{
			m_errorManager->addError(new Error(IdentifierInUse,
							"Procedure or function, '" + procedureName + "', has not been declared.",
							m_scanner->lineno()));
		}
		else if (procedureSymbol->getSymbolType() != Symbol::ProcedureSymbol
			&& procedureSymbol->getSymbolType() != Symbol::FunctionSymbol)
		{
			m_errorManager->addError(new Error(IdentifierInUse,
							"'" + procedureName + "' is not a procedure or function.",
							m_scanner->lineno()));
		}
		else
		{
			checkInvocationArgs(procedureSymbol, params);
		}
		
	}

	void SemanticHelper::checkInvocationArgs(Symbol* fpSymbol, 
							InvocationParameters* args)
	{
		if (fpSymbol->getProcClass() == BuiltInInput
			|| fpSymbol->getProcClass() == BuiltInOutput)
		{
			// check args are all valid for a IO procedure
			InvocationParameters::iterator it;
			for (it = args->begin(); it != args->end(); ++it)
			{
				Type* paramType = (*it).type;
				if (paramType != NULL)
				{
					if (paramType->getTypeClass() == Type::SimpleType)
					{
						// integer, real, boolean, char all ok
						continue;
					}
					else if (paramType->getTypeClass() == Type::StringLiteralType
						&& fpSymbol->getProcClass() == BuiltInOutput)
					{
						// strings are OK for built-in output procedures
						continue;
					}
					else if (paramType->getTypeClass() == Type::ArrayType)
					{
						// must be array of char indexed by integers starting at 1
						if (paramType->getElementType() == getCharType()
							&& paramType->getIndexType() == getIntegerType()
							&& paramType->getIndexRange().start == 1)
						{
							continue;
						}
					}
				}

				m_errorManager->addError(new Error(SemanticError,
								"Invalid argument for IO procedure, '" + fpSymbol->getName() + "'.",
								m_scanner->lineno()));
			}
		}
		else if (fpSymbol->getParameterCount() != args->size())
		{
			if (args->size() < fpSymbol->getParameterCount())
			{
				m_errorManager->addError(new Error(IdentifierInUse,
								"Function/procedure, '" + fpSymbol->getName() + "', is missing parameters.",
								m_scanner->lineno()));
			}
			else
			{
				m_errorManager->addError(new Error(IdentifierInUse,
								"Function/procedure, '" + fpSymbol->getName() + "', has too many parameters.",
								m_scanner->lineno()));
			}
		}
		else
		{
			const std::vector<Symbol*>* params;
			Type * t1;
			Type * t2;

			params = fpSymbol->getParameters();
			for(unsigned int i = 0; i < args->size(); i++)
			{
				t1 = params->at(i)->getType();
				t2 = args->at(i).type;

				// if param is a var param...
				if (params->at(i)->isVarParam() == true)
				{
					if (!checkAssignmentCompatible(t2, t1))
					{
						m_errorManager->addError(new Error(SemanticError,
									"Var parameter, '" + params->at(i)->getName() + "', not assignable to argument type.",
									m_scanner->lineno()));
					}
					else if (args->at(i).assignable == false)
					{
						m_errorManager->addError(new Error(SemanticError,
									"Variable argument required for var parameter, '" + params->at(i)->getName() + "'.",
									m_scanner->lineno()));
					}

					// t1 must be assignable! (not a constant)
				}
				else if (!checkAssignmentCompatible(t1, t2))
				{
					m_errorManager->addError(new Error(SemanticError,
								"Mismatch of argument types.",
								m_scanner->lineno()));
				}
			}
		}
	}

	// returns type for field of record
	// assignable = true if valid field access
	// offset = offset for field from start of record
	Type* SemanticHelper::getRecordFieldType(Type* recordType, string fieldName, bool& assignable, int& offset)
	{
		Type* fieldType = NULL;

		assignable = false; // only assignable if valid record.field access
		offset = 0;

		if (recordType == NULL)
		{
			// TODO error, or just ignore?
		}
		else if (recordType->getTypeClass() != Type::RecordType)
		{
			m_errorManager->addError(new Error(SemanticError,
					"Accessing field '" + fieldName + "' on type that is not a record", 
					m_scanner->lineno()));
		}
		else
		{
			IdTypePairList* fields = recordType->getFields();

			if (fields == NULL)
			{
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
						
						// valid field access, is assignable
						assignable = true;
						break;
					}

					offset += (*it)->second->getTypeSize();
				}
			}

			if (fieldType == NULL)
			{
				m_errorManager->addError(new Error(SemanticError,
						"Invalid field, '" + fieldName + "', for record.",
						m_scanner->lineno()));
			}
		}

		return fieldType;
	}

	Type* SemanticHelper::getSubscriptedArrayType(Type* arrayType, Type* subscriptType, bool& assignable)
	{
		Type* result = NULL;

		assignable = false; // only assignable if valid array access

		if (arrayType == NULL)
		{
			// TODO error or just ignore and return null?
		}
		else if (arrayType->getTypeClass() != Type::ArrayType)
		{
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
				assignable = true; // presumably (aside from runtime bounds check) is valid array access
			}
		}
		return result;
	}

	bool SemanticHelper::checkDuplicateField(IdTypePairList* fields, IdTypePair* field)
	{
		IdTypePairList::iterator it;
		for (it = fields->begin(); it != fields->end(); ++it)
		{
			if ((*it)->first->compare(*field->first) == 0)
			{
				m_errorManager->addError(
					new Error(InvalidRecordDecl,
						  "Duplicate field name, '" + *(*it)->first + "', in record declaration.",
						  m_scanner->lineno()));
				return true;
			}
		}

		return false;
	}
}

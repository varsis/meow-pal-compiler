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

		// add predefined constants
		Symbol* trueSymbol = new Symbol("true", Symbol::ConstantSymbol);
		trueSymbol->setType(getBooleanType());
		m_table->addSymbol(trueSymbol);

		Symbol* falseSymbol = new Symbol("false", Symbol::ConstantSymbol);
		falseSymbol->setType(getBooleanType());
		m_table->addSymbol(falseSymbol);

		// add predefined procedures + functions
		// writeln, readln
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
		// TODO see section on types in pal reference
		return false;
	}

}

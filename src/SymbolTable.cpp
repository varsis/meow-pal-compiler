#include "SymbolTable.hpp"
#include "EntryList.hpp"
#include <string>

namespace Meow
{
	SymbolTable::SymbolTable()
		: m_booleanType(true)
		, m_integerType(true)
		, m_realType(true)
		, m_charType(true)
	{
		m_currentLevel = 0;

		// TODO - add raw predefined types to table
	}

	SymbolTable::~SymbolTable()
	{
		std::tr1::unordered_map<std::string, EntryList*>::iterator i;

		// Go through the table and delete all the entry lists
		for(i=m_symbolTable.begin(); i != m_symbolTable.end(); i++)
		{
			delete i->second;
		}
	}

	void SymbolTable::addSymbol(Symbol * symbol)
	{
		EntryList* list;

		// Make sure that we have allocated space 
		// if the name hasn't been seen
		if (m_symbolTable.count(symbol->getName()) == 0)
		{
			list = new EntryList();
			m_symbolTable[symbol->getName()] = list;
		}
		else 
		{
			list = m_symbolTable[symbol->getName()];
		}

		list->addEntry(symbol, m_currentLevel);
	}

	Symbol* SymbolTable::getSymbolCurLevel(std::string name)
	{
		EntryList* list;
		
		// If we know its not in any scope
		if (m_symbolTable.count(name) == 0)
		{
			return NULL;
		}

		list = m_symbolTable[name];
		return list->getCurLevelEntry(m_currentLevel);
	}

	Symbol* SymbolTable::getSymbol(std::string name)
	{
		EntryList* list;

		// If we know its not in any scope
		if (m_symbolTable.count(name) == 0)
		{
			return NULL;
		}

		list = m_symbolTable[name];
		return list->getEntry();
	}

	void SymbolTable::incLevel() 
	{
		m_currentLevel++;
	}

	void SymbolTable::decLevel()
	{
		std::tr1::unordered_map<std::string, EntryList*>::iterator i;
		
		// Make sure that we aren't at zero since -1 scope is wrong
		if (m_currentLevel != 0)
		{
			m_currentLevel--;
		}

		// Set all the entry (scope) lists to max of current level
		for(i=m_symbolTable.begin(); i != m_symbolTable.end(); i++)
		{
			i->second->setLexLevel(m_currentLevel);
		}
	}

	int SymbolTable::getCurLevel()
	{
		return m_currentLevel;
	}

	// unary operators
	Type* SymbolTable::getOpResultType(Operator op, Type* type)
	{
		switch (op)
		{
			case OpPLUS:
				if (type == getRawRealType() || type == getRawIntegerType())
				{
					return type;
				}
				break;

			case OpMINUS:
				if (type == getRawRealType() || type == getRawIntegerType())
				{
					return type;
				}
				break;

			case OpNOT:
				// TODO eg how to treat type newBool = boolean;
				// can we treat newBool like predefined boolean as long as we don't mix the types?
				if (type == getRawBooleanType())
				{
					return type;
				}

				break;

			default:
				break;
		}

		return NULL;
	}

	Type* SymbolTable::getOpResultType(Operator op, Type* leftType, Type* rightType)
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
					return getRawBooleanType();
				}
				break;

			// arithmetic ops

			// TODO can't you collapse ADD/SUB/MULT together?
			case OpADD:
				if (checkCompatible(leftType, rightType))
				{
					// TODO eg how to treat type newInt = integer;
					// can we add newInts together? would need Type to define getRawType()
					// so we know if addition is valid or not

					if ((leftType == getRawIntegerType() || leftType == getRawRealType())
						&&(rightType == getRawIntegerType() || rightType == getRawRealType()))
					{
						// result is real if one operand is real
						if (leftType == getRawRealType() || rightType == getRawRealType())
						{
							return getRawRealType(); // the predefined real type
						}

						// otherwsie result is same type
						return leftType;
					}
				}
				break;

			case OpSUBTRACT:
				if (checkCompatible(leftType, rightType))
				{
					if ((leftType == getRawIntegerType() || leftType == getRawRealType())
						&&(rightType == getRawIntegerType() || rightType == getRawRealType()))
					{
						// result is real if one operand is real
						if (leftType == getRawRealType() || rightType == getRawRealType())
						{
							return getRawRealType(); // the predefined real type
						}

						// otherwsie result is same type
						return leftType;
					}
				}
				break;

			case OpMULTIPLY:
				if (checkCompatible(leftType, rightType))
				{
					if ((leftType == getRawIntegerType() || leftType == getRawRealType())
						&&(rightType == getRawIntegerType() || rightType == getRawRealType()))
					{
						// result is real if one operand is real
						if (leftType == getRawRealType() || rightType == getRawRealType())
						{
							return getRawRealType(); // the predefined real type
						}

						// otherwsie result is same type
						return leftType;
					}
				}
				break;

			case OpREALDIVIDE:
				if (checkCompatible(leftType, rightType))
				{
					if ((leftType == getRawIntegerType() || leftType == getRawRealType())
						&&(rightType == getRawIntegerType() || rightType == getRawRealType()))
					{
						return getRawRealType(); // the predefined real type
					}
				}
				break;

			case OpINTDIVIDE:
				if (checkCompatible(leftType, rightType))
				{
					if (leftType == getRawIntegerType() && rightType == getRawIntegerType())
					{
						return getRawIntegerType();
					}
				}
				break;

			case OpMOD:
				if (checkCompatible(leftType, rightType))
				{
					if (leftType == getRawIntegerType() && rightType == getRawIntegerType())
					{
						return getRawIntegerType();
					}
				}
				break;

			// logical ops
			case OpOR:
			case OpAND:
				if (checkCompatible(leftType, rightType))
				{
					if (leftType == getRawBooleanType() && rightType == getRawBooleanType())
					{
						return getRawBooleanType();
					}
				}
				break;

			default:
				break;

		}

		// if not compatible, return null
		return NULL;
	}

	bool SymbolTable::checkCompatible(Type* ltype, Type* rtype)
	{
		// see section on types in pal reference

		// compatible if they are the exact same type
		if (ltype == rtype)
		{
			return true;
		}

		// if strings, compatible if the same number of components
		/*
		   if (ltype->isStringType() && rtype->isStringType()
		   && ltype->componentCount == rtype->componentCount)
		   {
		   return true;
		   }
		   */

		// compatable if types are the predefined integer / real types
		if ((ltype == getRawIntegerType() || ltype == getRawRealType())
			&& (rtype == getRawIntegerType() || rtype == getRawRealType()))
		{
			return  true;
		}

		// otherwise, incompatible!
		return false;
	}

	bool SymbolTable::checkAssignmentCompatible(Type* ltype, Type* rtype)
	{
		// TODO see section on types in pal reference
		return false;
	}

}



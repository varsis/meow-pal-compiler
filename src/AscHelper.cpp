#include <fstream>
#include <sstream>

#include "AscHelper.hpp"
#include "ErrorManager.hpp"
#include "Scanner.hpp"
#include "SymbolTable.hpp"
#include "Type.hpp"

namespace Meow
{
	AscHelper::AscHelper(ofstream& ascOutput, SymbolTable* table, SemanticHelper* semanticHelper)
		: m_ascOutput(ascOutput)
		, m_symbolTable(table)
		, m_semanticHelper(semanticHelper)
		, m_errorManager(semanticHelper->getErrorManager())
		, m_nextLabel(0)
	{
	}

	string AscHelper::currentLabel(int offset)
	{
		stringstream ss;
		ss << "label_" << m_labelStack.back() + offset;
		return ss.str();
	}

	void AscHelper::reserveLabels(int count)
	{
		m_labelStack.push_back(m_nextLabel);
		m_nextLabel += count;
	}

	void AscHelper::popLabels()
	{
		m_labelStack.pop_back();
	}
	
	void AscHelper::simpleExpressionHelper(Type *typeOne, Type* typeTwo, string functionName) {
		// add top two values of stack
		if (typeOne == m_semanticHelper->getIntegerType() && typeTwo == m_semanticHelper->getIntegerType())
		{
			// if integer ...
			out() << "\t" << functionName << "I" << endl;
		}
		else if(typeOne == m_semanticHelper->getRealType() && typeTwo == m_semanticHelper->getRealType())
		{
			// if real ...
			out() << "\t" << functionName << "R" << endl;
		} else if(typeOne == m_semanticHelper->getRealType() && typeTwo == m_semanticHelper->getIntegerType())
		{
			// real than int
			out() << "\tITOR" << endl;
			out() << "\t" << functionName << "R" << endl;
		}
		else
		{
			// Int than real
			out() << "\tADJUST -1" << endl;
			out() << "\tITOR" << endl;
			out() << "\tADJUST 1" << endl;
			out() << "\t" << functionName << "R" << endl;
			
		}
	}
	
	void AscHelper::simpleExpressionMod() {
		// these are integer
			out() << "\tMOD" << endl;
			out() << "\tIFERR division_zero" << endl;
	}
	

	void AscHelper::invokeProcedure(string procedureName,
			InvocationParameters* params)
	{

		if (m_errorManager->getErrors()->size() > 0)
		{
			return;
		}

		Symbol* procedureSymbol = m_symbolTable->getSymbol(procedureName);

		if (procedureSymbol == NULL)
		{
			return;
		}

		// Note: at this point, we can assume arugments have been correctly pushed onto stack
		// Note: as the grammar is currently -- args pushed in order of appearance

		// free stack space used for arguments
		int argumentSpace = 0;
		InvocationParameters::iterator it;
		for (it = params->begin(); it != params->end(); ++it)
		{
			argumentSpace += it->type->getTypeSize();
		}

		// TODO this will need to consider what else may be on the stack 
		// (return value placeholder, display pointer, program counter, etc)
		int argPointer = -argumentSpace + 1;

		// handle builtin procedures

		if (procedureSymbol == m_semanticHelper->getWrite()
			|| procedureSymbol == m_semanticHelper->getWriteln())
		{

			argPointer = 0; // here we haven't touched the display pointer
			// split into separate write_* calls for each
			// argument according to arg type
			InvocationParameters::iterator it;
			for (it = params->begin(); it != params->end(); ++it)
			{
				if (it->type == m_semanticHelper->getIntegerType())
				{
					// TODO need current display index?
					m_ascOutput << "\tPUSH " << argPointer << "["<< m_symbolTable->getCurLevel() <<"]" << endl;
					m_ascOutput << "\tWRITEI" << endl;
					//m_ascOutput << "\tCALL 0, ml_write_integer" << endl;
				}
				else if (it->type == m_semanticHelper->getCharType())
				{
					m_ascOutput << "\tPUSH " << argPointer << "["<< m_symbolTable->getCurLevel() <<"]" << endl;
					m_ascOutput << "\tWRITEC" << endl;
				}
				else if (it->type == m_semanticHelper->getRealType())
				{
					m_ascOutput << "\tPUSH " << argPointer << "["<< m_symbolTable->getCurLevel() <<"]" << endl;
					m_ascOutput << "\tWRITER" << endl;
					//m_ascOutput << "\tCALL 0, ml_write_real" << endl;
				}
				else if (m_semanticHelper->isStringType(it->type) || it->type->getTypeClass() == Type::StringLiteralType)
				{
					m_ascOutput << "\tCONSTI " << argPointer << endl;
					m_ascOutput << "\tCALL 0, ml_write_string" << endl;
				}

				argPointer += it->type->getTypeSize();
			}
		}

		if (procedureSymbol == m_semanticHelper->getWriteln())
		{
			// write a newline (ascii character 10)
			m_ascOutput << "\tCONSTI 10" << endl;
			m_ascOutput << "\tWRITEC" << endl;
		}

		m_ascOutput << "\tADJUST -" << argumentSpace << endl;
	}
}


#include <fstream>
#include <sstream>
#include <vector>

#include "AscHelper.hpp"
#include "ErrorManager.hpp"
#include "Scanner.hpp"
#include "SymbolTable.hpp"
#include "Type.hpp"
#include "Symbol.hpp"

extern std::vector<int> g_offsetList;

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
		if (m_labelStack.size() > 0)
		{
			ss << "label_" << m_labelStack.back() + offset;
		}
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

		int argumentSpace = 0;
		InvocationParameters::iterator it;
		for (it = params->begin(); it != params->end(); ++it)
		{
			argumentSpace += it->type->getTypeSize();
		}

		// handle builtin procedures

		if (procedureSymbol == m_semanticHelper->getWrite())
		{
			invokeWrite(params);
		}
		else if (procedureSymbol == m_semanticHelper->getWriteln())
		{
			invokeWriteln(params);
		}

		// Ordinary procedures/functions...
		std::string label = procedureSymbol->getLabel();
		if (label.size() > 0)
		{
			// allocate space for return val 
			// TODO only if necessary?
			int returnValSize = 1; // TODO
			m_ascOutput << "\tADJUST " << returnValSize << endl;

			m_ascOutput << "\tCALL " << procedureSymbol->getLexLevel() + 1 << ", "
						<< label << endl;

			// return value now on top of stack, need to pop it to start of args
			// this seems way too complicated for this, but the only way to
			// store to a register is with CALL... :S

			reserveLabels(2);
			m_ascOutput << "\tCALL 0, " << currentLabel(0) << endl;
			m_ascOutput << "\tGOTO " << currentLabel(1) << endl;
			m_ascOutput << currentLabel(0) << endl;
			m_ascOutput << "\tPUSH -3[0]" << endl;
			m_ascOutput << "\tPOP -" << argumentSpace + 3 << "[0]" << endl;
			m_ascOutput << "\tRET 0" << endl;
			m_ascOutput << currentLabel(1) << endl;
			popLabels();

			m_ascOutput << "\tADJUST -" << returnValSize << endl;
		}

		if (argumentSpace > 0)
		{
			m_ascOutput << "\tADJUST -" << argumentSpace << endl;
		}
	}

	void AscHelper::invokeWriteln(InvocationParameters* params)
	{
		invokeWrite(params);

		// write a newline (ascii character 10)
		m_ascOutput << "\tCONSTI 10" << endl;
		m_ascOutput << "\tWRITEC" << endl;
	}

	void AscHelper::invokeWrite(InvocationParameters* params)
	{
		// Need to call a 'function' so we can get arguments offset from a display reg
		reserveLabels(2);
		m_ascOutput << "\tCALL 0, " << currentLabel(0) << endl;
		m_ascOutput << "\tGOTO " << currentLabel(1) << endl;
		m_ascOutput << currentLabel(0) << endl;

		int argumentSpace = 0;
		InvocationParameters::iterator it;
		for (it = params->begin(); it != params->end(); ++it)
		{
			argumentSpace += it->type->getTypeSize();
		}
		int argPointer = - 2 - argumentSpace; // pointer to first arg relative to display reg 0

		// split into separate write_* calls for each
		// argument according to arg type
		for (it = params->begin(); it != params->end(); ++it)
		{
			if (it->type == m_semanticHelper->getIntegerType())
			{
				m_ascOutput << "\tPUSH " << argPointer << "[0]" << endl;
				m_ascOutput << "\tWRITEI" << endl;
				//m_ascOutput << "\tCALL 0, ml_write_integer" << endl;
			}
			else if (it->type == m_semanticHelper->getCharType())
			{
				m_ascOutput << "\tPUSH " << argPointer << "[0]" << endl;
				m_ascOutput << "\tWRITEC" << endl;
			}
			else if (it->type == m_semanticHelper->getRealType())
			{
				m_ascOutput << "\tPUSH " << argPointer << "[0]" << endl;
				m_ascOutput << "\tWRITER" << endl;
				//m_ascOutput << "\tCALL 0, ml_write_real" << endl;
			}
			else if (m_semanticHelper->isStringType(it->type) || it->type->getTypeClass() == Type::StringLiteralType)
			{
				// push pointer to start of string
				m_ascOutput << "\tPUSHA " << argPointer << "[0]" << endl;
				m_ascOutput << "\tCALL 0, ml_write_string" << endl;
				m_ascOutput << "\tADJUST -1" << endl;
			}

			argPointer += it->type->getTypeSize();
		}

		m_ascOutput << "\tRET 0" << endl;
		m_ascOutput << currentLabel(1) << endl;
		popLabels();
	}

	void AscHelper::allocVariable(Symbol* sym)
	{
		if (sym)
		{
			m_ascOutput << "\tADJUST " << sym->getSizeInMem() << endl;
		}
	}

	void AscHelper::accessVariable(Symbol* sym)
	{
		if (sym)
		{
			m_ascOutput << "\tPUSH " << sym->getLocation() << "[" << sym->getLexLevel() << "]" << endl;
		}
	}	

	void AscHelper::assignToVariable(Symbol* sym)
	{
		if (sym)
		{
			m_ascOutput << "\tPOP " << sym->getLocation() << "[" << sym->getLexLevel() << "]" <<endl;
		}
	}

	void AscHelper::deallocVariables()
	{
		if (g_offsetList.size() >= 1)
		{
			m_ascOutput << "\tADJUST -" << g_offsetList[g_offsetList.size()-1] << endl;
			g_offsetList.pop_back();
		}
	}
}


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
			InvocationParameters* args)
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
		for (it = args->begin(); it != args->end(); ++it)
		{
			argumentSpace += it->type->getTypeSize();
		}

		// handle builtin procedures

		if (procedureSymbol == m_semanticHelper->getWrite())
		{
			invokeWrite(args);
		}
		else if (procedureSymbol == m_semanticHelper->getWriteln())
		{
			invokeWriteln(args);
		}

		// Ordinary procedures/functions...
		std::string label = procedureSymbol->getLabel();
		if (label.size() > 0)
		{
			int returnValSize = 0;
			if (procedureSymbol->getSymbolType() == Symbol::FunctionSymbol)
			{
				// allocate space for return val 
				returnValSize = procedureSymbol->getType()->getTypeSize();
				m_ascOutput << "\tADJUST " << returnValSize << endl;
			}

			// Actually call the routine
			m_ascOutput << "\tCALL " << procedureSymbol->getLexLevel() + 1 << ", "
						<< label << endl;

			// Copy any var parameters back to their sources (as per "copy-restore")
			// TODO mention 'copy-restore' strategy and ratinale in docs!
			for (unsigned int argIdx = 0; argIdx < procedureSymbol->getParameterCount(); ++argIdx)
			{
				Symbol* param = procedureSymbol->getParameters()->at(argIdx);
				if (param->isVarParam())
				{
					LValue arg = args->at(argIdx);

					reserveLabels(2);
					m_ascOutput << "\tCALL 0, vp" << currentLabel(0) << endl;
					m_ascOutput << "\tGOTO " << currentLabel(1) << endl;
					m_ascOutput << "vp" << currentLabel(0) << endl;

					for (int i = 0; i < arg.type->getTypeSize(); i++)
					{
						m_ascOutput << "\tPUSH " << param->getLocation() + i << "[0]" << endl;
						m_ascOutput << "\tPOP " << arg.offset + i << "[" << arg.level << "]" << endl;
					}

					m_ascOutput << "\tRET 0" << endl;
					m_ascOutput << currentLabel(1) << endl;
					popLabels();
				}
			}

			if (returnValSize > 0 && argumentSpace > 0)
			{
				// return value now on top of stack, need to pop it to start of args
				// this seems way too complicated for this, but the only way to
				// store to a register is with CALL... :S

				reserveLabels(2);
				m_ascOutput << "\tCALL 0, " << currentLabel(0) << endl;
				m_ascOutput << "\tGOTO " << currentLabel(1) << endl;
				m_ascOutput << currentLabel(0) << endl;

				for (int i = 0; i < returnValSize; i++)
				{
					m_ascOutput << "\tPUSH -" << 3 + i << "[0]" << endl;
					m_ascOutput << "\tPOP -" << argumentSpace + 3 + i << "[0]" << endl;
				}

				m_ascOutput << "\tRET 0" << endl;
				m_ascOutput << currentLabel(1) << endl;
				popLabels();
			}
		}

		if (argumentSpace > 0)
		{
			m_ascOutput << "\tADJUST -" << argumentSpace << endl;
		}
	}

	void AscHelper::invokeWriteln(InvocationParameters* args)
	{
		invokeWrite(args);

		// write a newline (ascii character 10)
		m_ascOutput << "\tCONSTI 10" << endl;
		m_ascOutput << "\tWRITEC" << endl;
	}

	void AscHelper::invokeWrite(InvocationParameters* args)
	{
		// Need to call a 'function' so we can get arguments offset from a display reg
		reserveLabels(2);
		m_ascOutput << "\tCALL 0, " << currentLabel(0) << endl;
		m_ascOutput << "\tGOTO " << currentLabel(1) << endl;
		m_ascOutput << currentLabel(0) << endl;

		int argumentSpace = 0;
		InvocationParameters::iterator it;
		for (it = args->begin(); it != args->end(); ++it)
		{
			argumentSpace += it->type->getTypeSize();
		}
		int argPointer = - 2 - argumentSpace; // pointer to first arg relative to display reg 0

		// split into separate write_* calls for each
		// argument according to arg type
		for (it = args->begin(); it != args->end(); ++it)
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

	void AscHelper::accessVariable(LValue lvalue)
	{
		// only do this if there are no errors -- bad type sizes can make this thing run
		// a lonnggg time!
		if (m_errorManager->getErrors()->size() == 0 && lvalue.type)
		{
			if (lvalue.sym->getSymbolType() == Symbol::ConstantSymbol)
			{
				// Actual constant value already pushed onto stack!
				return;
			}

			// otherwise, address of variable should be on stack

			int size = lvalue.type->getTypeSize();
			// Adjust for space of value
			m_ascOutput << "\tADJUST " << size - 1 << endl;

			reserveLabels(2);
			m_ascOutput << "\tCALL 0, " << currentLabel(0) << endl;
			m_ascOutput << "\tGOTO " << currentLabel(1) << endl;
			m_ascOutput << currentLabel(0) << endl;

			// Copy address to top of stack
			m_ascOutput << "\tPUSH " << -2 - size << "[0]" << endl;

			for (int i = 0; i < size; ++i)
			{
				m_ascOutput << "\tDUP" << endl;
				m_ascOutput << "\tCONSTI " << i << endl;
				m_ascOutput << "\tADDI" << endl;

				// Push element to stack
				m_ascOutput << "\tPUSHI " << lvalue.level << endl;
				// Pop element into place
				m_ascOutput << "\tPOP " << - 2 - size + i << "[0]" << endl;
			}

			m_ascOutput << "\tADJUST " << -1 << endl;

			m_ascOutput << "\tRET 0" << endl;
			m_ascOutput << currentLabel(1) << endl;
			popLabels();
		}
	}	

	void AscHelper::pushConstantValue(Symbol* symbol)
	{
		Type* type = symbol->getType();
		if (type)
		{
			switch (type->getTypeClass())
			{
			case Type::SimpleType:
				if (type == m_semanticHelper->getRealType())
				{
					// push real
					m_ascOutput << "\tCONSTR " << symbol->getConstantValue().real_val << endl;
				}
				else
				{
					// push boolean, char, integer as integer value
					m_ascOutput << "\tCONSTI " << symbol->getConstantValue().int_val << endl;
				}
				break;
			case Type::EnumeratedType:
				// push enum type entry thing as its integer value
				m_ascOutput << "\tCONSTI " << symbol->getConstantValue().int_val << endl;
				break;
			case Type::StringLiteralType:
				// TODO push a bunch of chars as integers with a terminating null
				break;
			default:
				// Other types aren't valid constants!
				break;
			}
		}
	}

	void AscHelper::assignToVariable(LValue lvalue)
	{
		if (m_errorManager->getErrors()->size() == 0 && lvalue.type)
		{
			// address should be right below value on stack

			reserveLabels(2);
			m_ascOutput << "\tCALL 0, " << currentLabel(0) << endl;
			m_ascOutput << "\tGOTO " << currentLabel(1) << endl;
			m_ascOutput << currentLabel(0) << endl;

			int size = lvalue.type->getTypeSize();
			for (int i = 0; i < size; ++i)
			{
				// Push address to copy to
				m_ascOutput << "\tPUSH " << - size - 1 - 2 << "[0]" << endl;
				m_ascOutput << "\tCONSTI " << i << endl;
				m_ascOutput << "\tADDI" << endl;

				// Push element
				m_ascOutput << "\tPUSH " << - size + i - 2 << "[0]" << endl;

				// Copy element to target location
				m_ascOutput << "\tPOPI " << lvalue.level << endl;
			}

			m_ascOutput << "\tRET 0" << endl;
			m_ascOutput << currentLabel(1) << endl;
			popLabels();

			// free memory for address + value
			m_ascOutput << "\tADJUST -" << size + 1 << endl;
		}
	}

	void AscHelper::addArraySubscriptOffset(Type* arrayType)
	{
		if (arrayType == NULL)
		{
			return;
		}

		Type* elementType = arrayType->getElementType();

		if (elementType == NULL)
		{
			return;
		}

		// Index is on stack. Convert it to an integer index relative to start of array
		// TODO may need to convert char (or enum) indexes a little differently? but maybe not (TEST!)

		m_ascOutput << "\tCONSTI " << - arrayType->getIndexRange().start << endl;
		m_ascOutput << "\tADDI" << endl;

		// TODO run time bounds check probably needs to happen here! 

		// Multiply index by size of element (if greater than 1?)
		m_ascOutput << "\tCONSTI " << elementType->getTypeSize() << endl;
		m_ascOutput << "\tMULI" << endl;

		// Add to whatever offset already on the stack
		m_ascOutput << "\tADDI" << endl;
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


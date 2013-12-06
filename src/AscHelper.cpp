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
	AscHelper::AscHelper(ofstream& ascOutput, SymbolTable* table, SemanticHelper* semanticHelper,
				bool arrayBoundsFlag, bool languageExtensions)
		: m_ascOutput(ascOutput)
		, m_symbolTable(table)
		, m_semanticHelper(semanticHelper)
		, m_errorManager(semanticHelper->getErrorManager())
		, m_arrayBoundsFlag(arrayBoundsFlag)
		, m_languageExtensions(languageExtensions)
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
		
		// Make sure that we have no errors
		if (m_errorManager->getErrors()->size() > 0)
		{
			return;
		}

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
	
	
	void AscHelper::functionSquareRoot(Type *typeOne) {
		// add top two values of stack
		if (typeOne == m_semanticHelper->getRealType())
		{
			// if real
			out() << "\tCALL 0, ml_sqrt" << endl;
		}
		else
		{
			// int
			out() << "\tITOR" << endl;
			out() << "\tCALL 0, ml_sqrt" << endl;

		}
	}
	
	
	
	void AscHelper::simpleExpressionMod() {
		
		// Make sure that we have no errors
		if (m_errorManager->getErrors()->size() > 0)
		{
			return;
		}

		// these are integer
		out() << "\tMOD" << endl;
		out() << "\tIFERR division_zero" << endl;
	}
	

	void AscHelper::invokeProcedure(string procedureName, InvocationParameters* args)
	{
		// Make sure that we have no errors
		if (m_errorManager->getErrors()->size() > 0)
		{
			return;
		}

		// For the language extensions 
		if (m_languageExtensions)
		{
			if (procedureName.compare("ascDump") == 0)
			{
				m_ascOutput << "\tCALL 0, ml_asc_dump" << endl;
				return;
			}
			else if (procedureName.compare("ascTrace") == 0)
			{
				m_ascOutput << "\tCALL 0, ml_asc_trace" << endl;
				return;
			}
		}


		Symbol* procedureSymbol = m_symbolTable->getSymbol(procedureName);

		if (procedureSymbol == NULL)
		{
			return;
		}


		// Note: at this point, we can assume arugments have been correctly pushed onto stack
		// Note: as the grammar is currently -- args pushed in order of appearance

		int argumentSpace = 0;
		for (unsigned int argIdx = 0; argIdx < args->size(); ++argIdx)
		{
			if (procedureSymbol == m_semanticHelper->getRead() 
					|| procedureSymbol == m_semanticHelper->getReadln()
					|| ( procedureSymbol->getParameters()
					&& argIdx < procedureSymbol->getParameters()->size()
					&& procedureSymbol->getParameters()->at(argIdx)->isVarParam()))
			{
				argumentSpace += 1; // just an address
			}
			else
			{
				argumentSpace += args->at(argIdx).type->getTypeSize();
			}
		}

		// handle builtin procedures

		if (procedureSymbol == m_semanticHelper->getOrd()
			|| procedureSymbol == m_semanticHelper->getChr())
		{
			// noop
			return;
		}
		else if (procedureSymbol == m_semanticHelper->getWrite())
		{
			invokeWrite(args);
		}
		else if (procedureSymbol == m_semanticHelper->getWriteln())
		{
			invokeWriteln(args);
		}
		else if (procedureSymbol == m_semanticHelper->getRead())
		{
			invokeRead(args);
		}
		else if (procedureSymbol == m_semanticHelper->getReadln())
		{
			invokeReadln(args);
		}
		else if (procedureSymbol == m_semanticHelper->getTrunc())
		{
			m_ascOutput << "\tCALL 0, trunc" << endl;
			return;
		}
		else if (procedureSymbol == m_semanticHelper->getRound())
		{
			m_ascOutput << "\tCALL 0, round" << endl;
			return;
		}
		else if (procedureSymbol == m_semanticHelper->getSucc())
		{
			m_ascOutput << "\tCALL 0, ml_succ" << endl;
			return;
		}
		else if (procedureSymbol == m_semanticHelper->getPred())
		{
			m_ascOutput << "\tCALL 0, ml_pred" << endl;
			return;
		}
		else if (procedureSymbol == m_semanticHelper->getOdd())
		{
			m_ascOutput << "\tCALL 0, ml_odd" << endl;
			return;
		}
		else if (procedureSymbol == m_semanticHelper->getAbs())
		{
			invokeAbs(args);
			return;
		}
		else if (procedureSymbol == m_semanticHelper->getSqr())
		{
			invokeSqr(args);
			return;
		}
		else if (procedureSymbol == m_semanticHelper->getSqrt())
		{
			m_ascOutput << "\tCALL 0, ml_sqrt" << endl;
			return;
		}
		else if (procedureSymbol == m_semanticHelper->getSin())
		{
			m_ascOutput << "\tCALL 0, ml_sin" << endl;
			return;
		}
		else if (procedureSymbol == m_semanticHelper->getExp())
		{
			m_ascOutput << "\tCALL 0, ml_exp" << endl;
			return;
		}
		else if (procedureSymbol == m_semanticHelper->getLn())
		{
			m_ascOutput << "\tCALL 0, ml_ln" << endl;
			return;
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
			int level = procedureSymbol->getLexLevel() + (procedureSymbol->isRecursive() ? 0 : 1);
			m_ascOutput << "\tCALL " << level << ", " << label << endl;

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
					m_ascOutput << "\tPUSH -" << 2 + (returnValSize - i) << "[0]" << endl;
					m_ascOutput << "\tPOP -" << 2 + (argumentSpace + returnValSize - i) << "[0]" << endl;
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
		// Make sure that we have no errors
		if (m_errorManager->getErrors()->size() > 0)
		{
			return;
		}

		invokeWrite(args);

		// write a newline (ascii character 10)
		m_ascOutput << "\tCONSTI 10" << endl;
		m_ascOutput << "\tWRITEC" << endl;
	}

	void AscHelper::invokeWrite(InvocationParameters* args)
	{
		// Make sure that we have no errors
		if (m_errorManager->getErrors()->size() > 0)
		{
			return;
		}

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
	
	void AscHelper::invokeReadln(InvocationParameters* args)
	{
		invokeRead(args);
		// If last argument is not a string ... (read_string will read until newline!)
		if (args->size() > 0 && !m_semanticHelper->isStringType(args->back().type))
		{
			m_ascOutput << "\tCALL 0, ml_eat_nl" << endl;
		}
	}

	void AscHelper::invokeRead(InvocationParameters* args)
	{
		// Need to call a 'function' so we can get arguments offset from a display reg
		reserveLabels(2);
		m_ascOutput << "\tCALL 0, " << currentLabel(0) << endl;
		m_ascOutput << "\tGOTO " << currentLabel(1) << endl;
		m_ascOutput << currentLabel(0) << endl;

		//int argumentSpace = 0;
		int argumentSpace = args->size(); // all read args passed by reference
		int argPointer = - 2 - argumentSpace; // pointer to first arg relative to display reg 0

		// split into separate read_* calls for each
		// argument according to arg type
		InvocationParameters::iterator it;
		for (it = args->begin(); it != args->end(); ++it)
		{
			if (it->type == m_semanticHelper->getIntegerType())
			{
				// push the address
				m_ascOutput << "\tPUSH " << argPointer << "[0]" << endl;
				// read the value
				m_ascOutput << "\tREADI" << endl;
				// pop value to address
				m_ascOutput << "\tPOPI" << endl;
			}
			else if (it->type == m_semanticHelper->getCharType())
			{
				m_ascOutput << "\tPUSH " << argPointer << "[0]" << endl;
				m_ascOutput << "\tREADC" << endl;
				m_ascOutput << "\tPOPI" << endl;
			}
			else if (it->type == m_semanticHelper->getRealType())
			{
				m_ascOutput << "\tPUSH " << argPointer << "[0]" << endl;
				m_ascOutput << "\tREADR" << endl;
				m_ascOutput << "\tPOPI" << endl;
			}
			else if (m_semanticHelper->isStringType(it->type) || it->type->getTypeClass() == Type::StringLiteralType)
			{
				// push pointer to start of string
				m_ascOutput << "\tCONSTI " << it->type->getIndexRange().end - it->type->getIndexRange().start + 1 << endl;
				m_ascOutput << "\tPUSH " << argPointer << "[0]" << endl;
				m_ascOutput << "\tCALL 0, ml_read_string" << endl;
				m_ascOutput << "\tADJUST -2" << endl;
			}

			argPointer += it->type->getTypeSize();
		}

		m_ascOutput << "\tRET 0" << endl;
		m_ascOutput << currentLabel(1) << endl;
		popLabels();

	}

	void AscHelper::invokeAbs(InvocationParameters* args)
	{
		// value is on top of stack
		if (args->size() == 1)
		{
			if (args->at(0).type == m_semanticHelper->getRealType())
			{
				m_ascOutput << "\tCALL 0, ml_abs_real" << endl;
			}
			else
			{
				m_ascOutput << "\tCALL 0, ml_abs_int" << endl;
			}
		}
	}

	void AscHelper::invokeSqr(InvocationParameters* args)
	{
		// value is on top of stack
		if (args->size() == 1)
		{
			if (args->at(0).type == m_semanticHelper->getRealType())
			{
				m_ascOutput << "\tCALL 0, ml_sqr" << endl;
			}
			else
			{
				m_ascOutput << "\tCALL 0, ml_sqr_int" << endl;
			}
		}
	}

	void AscHelper::allocVariable(Symbol* sym)
	{
		// Make sure that we have no errors
		if (m_errorManager->getErrors()->size() > 0)
		{
			return;
		}


		if (sym)
		{
			m_ascOutput << "\tADJUST " << sym->getSizeInMem() << endl;
		}
	}

	void AscHelper::accessVariable(LValue lvalue)
	{
		// Make sure that we have no errors
		if (m_errorManager->getErrors()->size() > 0)
		{
			return;
		}

		if (lvalue.type)
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
				m_ascOutput << "\tPUSHI " << endl;
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
		// Make sure that we have no errors
		if (m_errorManager->getErrors()->size() > 0)
		{
			return;
		}

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
				{
					// Ugh why exactly did we put the string in the type!?
					// TODO we should probably move that to the symbol!
					string literal = type->getStringLiteral();
					for (string::iterator it = literal.begin(); it != literal.end(); ++it)
					{
						m_ascOutput << "\tCONSTI " << (int)(*it) << endl;
					}
					m_ascOutput << "\tCONSTI " << 0 << endl;
				}
				break;
			default:
				// Other types aren't valid constants!
				break;
			}
		}
	}

	void AscHelper::assignToVariable(LValue lvalue, Type* rtype)
	{
		// Make sure that we have no errors
		if (m_errorManager->getErrors()->size() > 0)
		{
			return;
		}

		if (lvalue.type && rtype)
		{
			// address should be right below value on stack
			reserveLabels(2);
			m_ascOutput << "\tCALL 0, " << currentLabel(0) << endl;
			m_ascOutput << "\tGOTO " << currentLabel(1) << endl;
			m_ascOutput << currentLabel(0) << endl;

			// don't copy more than the smallest type
			// (this is an issue for assigning string literals to char arrays)
			int size = min(lvalue.type->getTypeSize(), rtype->getTypeSize());
			for (int i = 0; i < size; ++i)
			{

				// Push address to copy to
				m_ascOutput << "\tPUSH " << - rtype->getTypeSize() - 1 - 2 << "[0]" << endl;
				m_ascOutput << "\tCONSTI " << i << endl;
				m_ascOutput << "\tADDI" << endl;

				if (m_semanticHelper->isStringType(lvalue.type) && i == size - 1)
				{
					// push a terminating null for the string!
					// (necessary if truncating a larger string literal)
					m_ascOutput << "\tCONSTI 0" << endl;
				}
				else
				{
					// Push element from RHS
					m_ascOutput << "\tPUSH " << - rtype->getTypeSize() + i - 2 << "[0]" << endl;
				}

				// Copy element to target location
				m_ascOutput << "\tPOPI" << endl;
			}

			m_ascOutput << "\tRET 0" << endl;
			m_ascOutput << currentLabel(1) << endl;
			popLabels();

			// free memory for address + value
			m_ascOutput << "\tADJUST -" << size + 1 << endl;
		}
	}
	void AscHelper::logicalExpression(std::string functionName) 
	{
                out() << "\t" << functionName << endl;
        }


	void AscHelper::comparisonExpression(Type* typeOne, Type* typeTwo, string functionName)
	{
		// Only valid for integers, booleans, characters, reals, and strings

                if (m_errorManager->getErrors()->size() > 0)
                {
                        return;
                }

                // add top two values of stack
                if (typeOne == m_semanticHelper->getIntegerType() && typeTwo == m_semanticHelper->getIntegerType())
                {
                        // if integer ...
                        out() << "\t" << functionName << "I" << endl;
                }
                else if (typeOne == m_semanticHelper->getRealType() && typeTwo == m_semanticHelper->getRealType())
                {
                        // if real ...
                        out() << "\t" << functionName << "R" << endl;
                } 
		else if (typeOne == m_semanticHelper->getRealType() && typeTwo == m_semanticHelper->getIntegerType())
                {
                        // real than int
                        out() << "\tITOR" << endl;
                        out() << "\t" << functionName << "R" << endl;
                }
                else if (typeOne == m_semanticHelper->getIntegerType() && typeTwo == m_semanticHelper->getRealType())
                {
                        // Int than real
                        out() << "\tADJUST -1" << endl;
                        out() << "\tITOR" << endl;
                        out() << "\tADJUST 1" << endl;
                        out() << "\t" << functionName << "R" << endl;   
                }
		else if (typeOne == m_semanticHelper->getBooleanType() && typeTwo == m_semanticHelper->getBooleanType())
		{
			out() << "\t" << functionName << "I" << endl;
		}
		else if (typeOne == m_semanticHelper->getCharType() && typeTwo == m_semanticHelper->getCharType())
		{
			out() << "\t" << functionName << "I" << endl;
		}
		else
		{
			// TODO: Handle string type
		}
	}

	void AscHelper::addArraySubscriptOffset(Type* arrayType)
	{
		// Make sure that we have no errors
		if (m_errorManager->getErrors()->size() > 0)
		{
			return;
		}

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

		m_ascOutput << "\tCONSTI " << - arrayType->getIndexRange().start << endl;
		m_ascOutput << "\tADDI" << endl;

		m_ascOutput << "\tDUP" << endl;
		m_ascOutput << "\tCONSTI " << arrayType->getIndexRange().end - arrayType->getIndexRange().start << endl;
		
		if (m_arrayBoundsFlag)
		{
			m_ascOutput << "\tCALL 0, ml_bcheck" << endl;
		}
		else
		{
			m_ascOutput << "\tCALL 0, ml_nobcheck" << endl;
		}
		m_ascOutput << "\tADJUST -2" << endl;

		// Multiply index by size of element (if greater than 1?)
		m_ascOutput << "\tCONSTI " << elementType->getTypeSize() << endl;
		m_ascOutput << "\tMULI" << endl;

		// Add to whatever offset already on the stack
		m_ascOutput << "\tADDI" << endl;
	}

	void AscHelper::deallocVariables()
	{
		// Make sure that we have no errors
		if (m_errorManager->getErrors()->size() > 0)
		{
			return;
		}

		if (g_offsetList.size() >= 1)
		{
			m_ascOutput << "\tADJUST -" << g_offsetList[g_offsetList.size()-1] << endl;
			g_offsetList.pop_back();
		}
	}

	bool AscHelper::shouldPassByRef(string routineName, unsigned int paramIndex)
	{
		Symbol* sym = m_symbolTable->getSymbol(routineName);
		if (sym)
		{
			const vector<Symbol*>* params = sym->getParameters();
			if (sym == m_semanticHelper->getRead()
				|| sym == m_semanticHelper->getReadln())
			{
				return  true;
			}
			else if (params && paramIndex < params->size())
			{
				return  params->at(paramIndex)->isVarParam();
			}
		}

		return false;
	}
	
	void AscHelper::compareStrings(Symbol * sym1, Symbol * sym2) {
		Symbol * tableSym1 = m_symbolTable->getSymbol(sym1->getName());
		Symbol * tableSym2 = m_symbolTable->getSymbol(sym2->getName());
		
		// Debug
		/*out() << "\t# Location 1 " << tableSym1->getLocation() << endl;
		out() << "\t# Size 1 " << tableSym1->getSizeInMem() << endl;
		
		out() << "\t# Location 2 " << tableSym2->getLocation() << endl;
		out() << "\t# Size 2 " << tableSym2->getSizeInMem() << endl;
		*/
				 
		if(tableSym1->getSizeInMem() == tableSym2->getSizeInMem()) {
			out() << "\tPUSHA " << tableSym1->getLocation() << "[" << tableSym1->getLexLevel() << "]" << endl;
			out() << "\tPUSHA " << tableSym2->getLocation() << "[" << tableSym2->getLexLevel() << "]" << endl;
			out() << "\tCONSTI 0 " << endl;
		
			out() << "\tCALL 0, ml_compare_strings" << endl;
		}
		else
		{
			out() << "\tCALL 0, ml_compare_noteq_strings" << endl;
		}
	}
}


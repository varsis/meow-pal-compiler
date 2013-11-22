#include <fstream>

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
	{
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

		// Note: at this point, we can  assume arugments have been correctly pushed onto stack

		// handle builtin procedures

		if (procedureSymbol == m_semanticHelper->getWrite()
			|| procedureSymbol == m_semanticHelper->getWriteln())
		{
			// split into separate write_* calls for each
			// argument according to arg type
			InvocationParameters::iterator it;
			for (it = params->begin(); it != params->end(); ++it)
			{
				if (it->type == m_semanticHelper->getIntegerType())
				{
					m_ascOutput << "\tDUP" << endl;
					m_ascOutput << "\tWRITEI" << endl;
					//m_ascOutput << "\tCALL 0, ml_write_integer" << endl;
				}
				else if (it->type == m_semanticHelper->getCharType())
				{
					m_ascOutput << "\tDUP" << endl;
					m_ascOutput << "\tWRITEC" << endl;
				}
				else if (it->type == m_semanticHelper->getRealType())
				{
					m_ascOutput << "\tDUP" << endl;
					m_ascOutput << "\tWRITER" << endl;
					//m_ascOutput << "\tCALL 0, ml_write_real" << endl;
				}
				else if (m_semanticHelper->isStringType(it->type) || it->type->getTypeClass() == Type::StringLiteralType)
				{
					m_ascOutput << "\tCALL 0, ml_write_string";
				}
			}
		}

		if (procedureSymbol == m_semanticHelper->getWriteln())
		{
			// write a newline (ascii character 10)
			m_ascOutput << "\tCONSTI 10" << endl;
			m_ascOutput << "\tWRITEC" << endl;
		}

		// free stack space used for arguments
		int argumentSpace = 0;
		InvocationParameters::iterator it;
		for (it = params->begin(); it != params->end(); ++it)
		{
			argumentSpace += it->type->getTypeSize();
		}
		m_ascOutput << "\tADJUST -" << argumentSpace << endl;
	}
}


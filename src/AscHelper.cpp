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
					// TODO -- need actual symbol for invocation param
					// so we can generate code to access it's value
					m_ascOutput << "\tCONSTI 23" << endl;
					m_ascOutput << "\tWRITEI" << endl;
					//m_ascOutput << "\tCALL 0, ml_write_integer" << endl;
				}
				else if (it->type == m_semanticHelper->getCharType())
				{
					// TODO -- need actual symbol for invocation param
					m_ascOutput << "\tCONSTI 90" << endl;
					m_ascOutput << "\tWRITEC" << endl;

				}
				else if (it->type == m_semanticHelper->getRealType())
				{
					// TODO -- need actual symbol for invocation param
					m_ascOutput << "\tCONSTR 6969.69" << endl;
					m_ascOutput << "\tWRITER" << endl;
				}
				else if (m_semanticHelper->isStringType(it->type))
				{
					// TODO -- need actual symbol for invocation param
					//m_ascOutput << "\tPUSHI <STRING POINTER>";
					//m_ascOutput << "\tCALL 0, ml_write_string";
				}
			}
		}

		if (procedureSymbol == m_semanticHelper->getWriteln())
		{
			// write a newline (ascii character 10)
			m_ascOutput << "\tCONSTI 10" << endl;
			m_ascOutput << "\tWRITEC" << endl;
		}
	}
}


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
		intSymbol->setType(m_table->getRawIntegerType());
		m_table->addSymbol(intSymbol);

		Symbol* realSymbol = new Symbol("real", Symbol::TypeSymbol);
		realSymbol->setType(m_table->getRawRealType());
		m_table->addSymbol(realSymbol);

		Symbol* charSymbol = new Symbol("char", Symbol::TypeSymbol);
		charSymbol->setType(m_table->getRawCharType());
		m_table->addSymbol(charSymbol);

		Symbol* boolSymbol = new Symbol("boolean", Symbol::TypeSymbol);
		boolSymbol->setType(m_table->getRawBooleanType());
		m_table->addSymbol(boolSymbol);

		// add predefined constants
		Symbol* trueSymbol = new Symbol("true", Symbol::ConstantSymbol);
		trueSymbol->setType(m_table->getRawBooleanType());
		m_table->addSymbol(trueSymbol);

		Symbol* falseSymbol = new Symbol("false", Symbol::ConstantSymbol);
		falseSymbol->setType(m_table->getRawBooleanType());
		m_table->addSymbol(falseSymbol);

		// add predefined procedures + functions
		// writeln, readln
	}

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
		return m_table->getRawIntegerType();
	}
}

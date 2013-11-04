#include "Declarations.hpp"
#include "ConstantDeclaration.hpp"
#include "TypeDeclaration.hpp"
#include "VariableDeclaration.hpp"
#include "ProcedureDeclaration.hpp"

namespace Meow
{
	Declarations::Declarations(ConstantDeclarationList* constDeclList,
				TypeDeclarationList* typeDeclList,
				VariableDeclarationList* variableDeclList,
				ProcedureDeclarationList* procedureDeclList)
		: m_constantDeclarationList(constDeclList)
		, m_typeDeclarationList(typeDeclList)
		, m_variableDeclarationList(variableDeclList)
		, m_procedureDeclarationList(procedureDeclList)
	{
	}
	
	void Declarations::acceptPreOrder(Visitor* visitor)
	{
		visitor->visit(this);

		if (m_constantDeclarationList)
		{
			ConstantDeclarationList::iterator constIt;
			for (constIt = m_constantDeclarationList->begin();
					constIt != m_constantDeclarationList->end();
					++constIt)
			{
				(*constIt)->acceptPreOrder(visitor);
			}
		}

		if (m_typeDeclarationList)
		{
			TypeDeclarationList::iterator typeIt;
			for (typeIt = m_typeDeclarationList->begin();
					typeIt != m_typeDeclarationList->end();
					++typeIt)
			{
				(*typeIt)->acceptPreOrder(visitor);
			}
		}

		if (m_variableDeclarationList)
		{
			VariableDeclarationList::iterator varIt;
			for (varIt = m_variableDeclarationList->begin();
					varIt != m_variableDeclarationList->end();
					++varIt)
			{
				(*varIt)->acceptPreOrder(visitor);
			}
		}

		if (m_procedureDeclarationList)
		{
			ProcedureDeclarationList::iterator procIt;
			for (procIt = m_procedureDeclarationList->begin();
					procIt != m_procedureDeclarationList->end();
					++procIt)
			{
				(*procIt)->acceptPreOrder(visitor);
			}
		}
	}

	void Declarations::acceptPostOrder(Visitor* visitor)
	{
		ConstantDeclarationList::iterator constIt;
		for (constIt = m_constantDeclarationList->begin();
				constIt != m_constantDeclarationList->end();
				++constIt)
		{
			(*constIt)->acceptPostOrder(visitor);
		}

		TypeDeclarationList::iterator typeIt;
		for (typeIt = m_typeDeclarationList->begin();
				typeIt != m_typeDeclarationList->end();
				++typeIt)
		{
			(*typeIt)->acceptPostOrder(visitor);
		}

		VariableDeclarationList::iterator varIt;
		for (varIt = m_variableDeclarationList->begin();
				varIt != m_variableDeclarationList->end();
				++varIt)
		{
			(*varIt)->acceptPostOrder(visitor);
		}

		ProcedureDeclarationList::iterator procIt;
		for (procIt = m_procedureDeclarationList->begin();
				procIt != m_procedureDeclarationList->end();
				++procIt)
		{
			(*procIt)->acceptPostOrder(visitor);
		}

		visitor->visit(this);
	}
	
	const ConstantDeclarationList* Declarations::getConstantDeclarationList() const
	{
		return m_constantDeclarationList;
	}
	
	const TypeDeclarationList* Declarations::getTypeDeclarationList() const
	{
		return m_typeDeclarationList;
	}
	
	const VariableDeclarationList* Declarations::getVariableDeclarationList() const
	{
		return m_variableDeclarationList;
	}
	
	const ProcedureDeclarationList* Declarations::getProcedureDeclarationList() const
	{
		return m_procedureDeclarationList;
	}
}

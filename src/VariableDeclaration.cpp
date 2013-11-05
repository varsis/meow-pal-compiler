#include "VariableDeclaration.hpp"
#include "Visitor.hpp"
#include "Type.hpp"
#include "Identifier.hpp"
#include "ASTListTypes.hpp"

namespace Meow
{
	VariableDeclaration::VariableDeclaration(int lineNumber, Type* type)
	: m_type(type)
	{
	}
	
	VariableDeclaration::~VariableDeclaration()
	{
		
	}
	
	void VariableDeclaration::acceptPreOrder(Visitor* visitor)
	{
		visitor->visit(this);

		m_type->acceptPreOrder(visitor);

		IdentifierList::iterator it;
		for (it = m_identifiers.begin(); it != m_identifiers.end(); ++it)
		{
			(*it)->acceptPreOrder(visitor);
		}
	}

	void VariableDeclaration::acceptPostOrder(Visitor* visitor)
	{
		m_type->acceptPostOrder(visitor);

		IdentifierList::iterator it;
		for (it = m_identifiers.begin(); it != m_identifiers.end(); ++it)
		{
			(*it)->acceptPostOrder(visitor);
		}

		visitor->visit(this);
	}
	
	void VariableDeclaration::addIdentifier(Identifier* id)
	{
		m_identifiers.push_back(id);
	}
	
	const vector<Identifier*>* VariableDeclaration::getIdentifiers() const
	{
		return &m_identifiers;
	}
	
	const Type* VariableDeclaration::getType() const
	{
		return m_type;
	}
}


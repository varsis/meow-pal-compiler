#include "Field.hpp"
#include "Visitor.hpp"
#include "Type.hpp"
#include "Identifier.hpp"
#include "ASTListTypes.hpp"

namespace Meow
{
	
	Field::Field(int lineNumber, Type* type)
	: m_type(type)
	{
	}
	
	Field::~Field()
	{
	}
	
	void Field::acceptPreOrder(Visitor* visitor)
	{
		visitor->visit(this);

		m_type->acceptPreOrder(visitor);

		IdentifierList::iterator it;
		for (it = m_identifiers.begin(); it != m_identifiers.end(); ++it)
		{
			(*it)->acceptPreOrder(visitor);
		}
	}

	void Field::acceptPostOrder(Visitor* visitor)
	{
		m_type->acceptPostOrder(visitor);

		IdentifierList::iterator it;
		for (it = m_identifiers.begin(); it != m_identifiers.end(); ++it)
		{
			(*it)->acceptPostOrder(visitor);
		}

		visitor->visit(this);
	}
	
	void Field::addIdentifier(Identifier* id)
	{
		m_identifiers.push_back(id);
	}
	
	const vector<Identifier*>* Field::getIdentifiers() const
	{
		return &m_identifiers;
	}
	
	const Type* Field::getType() const
	{
		return m_type;
	}
	
}


#include "Field.hpp"

namespace Meow
{
	
	Field::Field(int lineNumber, Type* type)
	: m_type(type)
	{
	}
	
	Field::~Field()
	{
	}
	
	void Field::accept(Visitor* visitor)
	{
	}
	
	const Type* Field::accept(TypeVisitor* typeVisitor)
	{
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
	}
	
}


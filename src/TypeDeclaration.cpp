#include "TypeDeclaration.hpp"

namespace Meow
{
	TypeDeclaration::TypeDeclaration(int lineNumber, Identifier* identifier, Type* type)
	: m_identifier(identifier)
	, m_type(type)
	{
	}
	
	void TypeDeclaration::accept(Visitor* visitor)
	{
	}
	const Type* TypeDeclaration::accept(TypeVisitor* typeVisitor)
	{
	}
	
	const Identifier* TypeDeclaration::getIdentifier() const
	{
		return m_identifier;
	}
	
	const Type* TypeDeclaration::getType() const
	{
		
	}
}

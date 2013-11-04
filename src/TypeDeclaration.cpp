#include "TypeDeclaration.hpp"
#include "Visitor.hpp"
#include "Identifier.hpp"
#include "Type.hpp"

namespace Meow
{
	TypeDeclaration::TypeDeclaration(int lineNumber, Identifier* identifier, Type* type)
		: m_identifier(identifier)
		, m_type(type)
	{
	}
	
	void TypeDeclaration::acceptPreOrder(Visitor* visitor)
	{
		visitor->visit(this);
		m_identifier->acceptPreOrder(visitor);
		m_type->acceptPreOrder(visitor);
	}

	void TypeDeclaration::acceptPostOrder(Visitor* visitor)
	{
		m_identifier->acceptPostOrder(visitor);
		m_type->acceptPostOrder(visitor);
		visitor->visit(this);
	}
	
	const Identifier* TypeDeclaration::getIdentifier() const
	{
		return m_identifier;
	}
	
	const Type* TypeDeclaration::getType() const
	{
		return m_type;
	}
}

#include "ConstantDeclaration.hpp"
#include "Identifier.hpp"

namespace Meow
{
	ConstantDeclaration::ConstantDeclaration(int lineNumber,
						Identifier* identifier,
						Expression* expression)
		: m_identifier(identifier)
	{
	}
	
	void ConstantDeclaration::accept(Visitor* visitor)
	{
	}
	
	const Type* ConstantDeclaration::getType() const
	{
		return m_type;
	}
	
	const Identifier* ConstantDeclaration::getIdentifier() const
	{
		return m_identifier;
	}
	
	const Expression* ConstantDeclaration::getExpression() const
	{
		return m_expression;
	}
}


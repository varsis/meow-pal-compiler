#include "ConstantDeclaration.hpp"
#include "Visitor.hpp"
#include "Identifier.hpp"
#include "Expression.hpp"

namespace Meow
{
	ConstantDeclaration::ConstantDeclaration(int lineNumber,
						Identifier* identifier,
						Expression* expression)
		: m_identifier(identifier)
		, m_expression(expression)
	{
	}
	
	void ConstantDeclaration::acceptPreOrder(Visitor* visitor)
	{
		visitor->visit(this);
		m_identifier->acceptPreOrder(visitor);
		m_expression->acceptPreOrder(visitor);
	}

	void ConstantDeclaration::acceptPostOrder(Visitor* visitor)
	{
		m_identifier->acceptPostOrder(visitor);
		m_expression->acceptPostOrder(visitor);
		visitor->visit(this);
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


#include "UnaryMinusExpression.hpp"
#include "Visitor.hpp"
#include "Expression.hpp"

namespace Meow
{
	UnaryMinusExpression::UnaryMinusExpression(Expression* operand)
		: m_operand(operand)
	{
	}
	
	void UnaryMinusExpression::acceptPreOrder(Visitor* visitor)
	{
		visitor->visit(this);
		m_operand->acceptPreOrder(visitor);
	}

	void UnaryMinusExpression::acceptPostOrder(Visitor* visitor)
	{
		m_operand->acceptPostOrder(visitor);
		visitor->visit(this);
	}
}


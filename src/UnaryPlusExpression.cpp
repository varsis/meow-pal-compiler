#include "UnaryPlusExpression.hpp"
#include "Visitor.hpp"
#include "Expression.hpp"

namespace Meow
{
	UnaryPlusExpression::UnaryPlusExpression(Expression* operand)
		: m_operand(operand)
	{
	}

	void UnaryPlusExpression::acceptPreOrder(Visitor* visitor)
	{
		visitor->visit(this);
		m_operand->acceptPreOrder(visitor);
	}

	void UnaryPlusExpression::acceptPostOrder(Visitor* visitor)
	{
		m_operand->acceptPostOrder(visitor);
		visitor->visit(this);
	}
}


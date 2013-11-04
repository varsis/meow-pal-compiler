#include "NotExpression.hpp"
#include "Visitor.hpp"
#include "Expression.hpp"

namespace Meow
{
	NotExpression::NotExpression(Expression* operand)
	: m_operand(operand)
	{
	}
	
	void NotExpression::acceptPreOrder(Visitor* visitor)
	{
		visitor->visit(this);
		m_operand->acceptPreOrder(visitor);
	}

	void NotExpression::acceptPostOrder(Visitor* visitor)
	{
		m_operand->acceptPostOrder(visitor);
		visitor->visit(this);
	}
}

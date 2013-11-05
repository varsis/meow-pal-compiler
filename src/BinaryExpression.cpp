#include "BinaryExpression.hpp"
#include "Visitor.hpp"
#include "Expression.hpp"

namespace Meow
{
	BinaryExpression::BinaryExpression(Expression* left, Expression* right)
		: m_left(left)
		, m_right(right)
	{
	}
	
	void BinaryExpression::acceptPreOrder(Visitor* visitor)
	{
		visitor->visit(this);
		m_left->acceptPreOrder(visitor);
		m_right->acceptPreOrder(visitor);
	}

	void BinaryExpression::acceptPostOrder(Visitor* visitor)
	{
		m_left->acceptPostOrder(visitor);
		m_right->acceptPostOrder(visitor);
		visitor->visit(this);
	}
}

#include "BinaryExpression.hpp"

namespace Meow
{
	BinaryExpression::BinaryExpression(Expression* left, Expression* right)
		: m_left(left)
		, m_right(right)
	{
	}
	
	void BinaryExpression::accept(Visitor* visitor)
	{
	}
	
	Type* BinaryExpression::accept(TypeVisitor* visitor)
	{
		return 0;
	}
	
}

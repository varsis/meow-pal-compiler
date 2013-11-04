#include "GreaterThanExpression.hpp"

namespace Meow
{
	
	GreaterThanExpression::GreaterThanExpression(Expression* left, Expression* right)
	: BinaryExpression(left, right)
	{
	}
	
	void GreaterThanExpression::accept(Visitor* visitor)
	{
	}
}


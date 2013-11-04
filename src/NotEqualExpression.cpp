#include "NotEqualExpression.hpp"

namespace Meow
{
	
	NotEqualExpression::NotEqualExpression(Expression* left, Expression* right)
	: BinaryExpression(left, right)
	{
	}
	
	void NotEqualExpression::accept(Visitor* visitor)
	{
	}
	
}


#include "GreaterThanEqualExpression.hpp"

namespace Meow
{
	
	GreaterThanEqualExpression::GreaterThanEqualExpression(Expression* left, Expression* right)
	: BinaryExpression(left, right)
	{
	}
	
	void GreaterThanEqualExpression::accept(Visitor* visitor)
	{
	}
	
}


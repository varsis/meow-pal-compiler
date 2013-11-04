#include "LessThanEqualExpression.hpp"

namespace Meow
{
	LessThanEqualExpression::LessThanEqualExpression(Expression* left, Expression* right)
	: BinaryExpression(left, right)
	{
	}
	
	void LessThanEqualExpression::accept(Visitor* visitor)
	{
	}
}


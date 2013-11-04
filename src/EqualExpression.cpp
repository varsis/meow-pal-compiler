#include "EqualExpression.hpp"

namespace Meow
{
	EqualExpression::EqualExpression(Expression* left, Expression* right)
	: BinaryExpression(left, right)
	{
	}
	
	void EqualExpression::accept(Visitor* visitor)
	{
	}
}


#include "LessThanExpression.hpp"

namespace Meow
{
	
	LessThanExpression::LessThanExpression(Expression* left, Expression* right)
	: BinaryExpression(left, right)
	{
	}
	
	void LessThanExpression::accept(Visitor* visitor)
	{
	}
	
}


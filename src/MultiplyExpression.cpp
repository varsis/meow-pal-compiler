#include "MultiplyExpression.hpp"

namespace Meow
{
	MultiplyExpression::MultiplyExpression(Expression* left, Expression* right)
	: BinaryExpression(left, right)
	{
	}
	
	void MultiplyExpression::accept(Visitor* visitor)
	{
	}
}


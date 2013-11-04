#include "OrExpression.hpp"

namespace Meow
{
	OrExpression::OrExpression(Expression* left, Expression* right)
	: BinaryExpression(left, right)
	{
	}
	
	void OrExpression::accept(Visitor* visitor)
	{
	}
	
}

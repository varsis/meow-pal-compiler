#include "AndExpression.hpp"

namespace Meow
{
	
	AndExpression::AndExpression(Expression* left, Expression* right)
		: BinaryExpression(left, right)
	{
	}
	
	void AndExpression::accept(Visitor* visitor)
	{
	}
}



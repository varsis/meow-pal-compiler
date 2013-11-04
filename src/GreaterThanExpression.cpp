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
	
	Type* GreaterThanExpression::accept(TypeVisitor* visitor)
	{
		return 0;
	}
	
}


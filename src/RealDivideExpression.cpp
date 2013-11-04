#include "RealDivideExpression.hpp"

namespace Meow
{
	
	RealDivideExpression::RealDivideExpression(Expression* left, Expression* right)
	: BinaryExpression(left, right)
	{
	}
	
	void RealDivideExpression::accept(Visitor* visitor)
	{
	}
	Type* RealDivideExpression::accept(TypeVisitor* visitor)
	{
		return 0;
	}
}


#include "IntDivideExpression.hpp"

namespace Meow
{
	
	IntDivideExpression::IntDivideExpression(Expression* left, Expression* right)
	: BinaryExpression(left, right)
	{
	}
	
	void IntDivideExpression::accept(Visitor* visitor)
	{
	}
	Type* IntDivideExpression::accept(TypeVisitor* visitor)
	{
		return 0;
	}
}



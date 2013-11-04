#include "SubtractExpression.hpp"

namespace Meow
{
	SubtractExpression::SubtractExpression(Expression* left, Expression* right)
	: BinaryExpression(left, right)
	{
	}
	
	void SubtractExpression::accept(Visitor* visitor)
	{
	}
	
	Type* SubtractExpression::accept(TypeVisitor* visitor)
	{
		return 0;
	}
	
}

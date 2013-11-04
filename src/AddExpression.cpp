#include "AddExpression.hpp"

namespace Meow
{
	AddExpression(Expression* left, Expression* right)
	: BinaryExpression(left, right)
	{
	}
	
	virtual void accept(Visitor* visitor)
	{
	}
	
	virtual Type* accept(TypeVisitor* visitor)
	{
		return 0;
	}
	
}



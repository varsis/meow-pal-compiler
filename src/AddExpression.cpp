#include "AddExpression.hpp"

namespace Meow
{
	AddExpression::AddExpression(Expression* left, Expression* right)
	: BinaryExpression(left, right)
	{
	}
	
	void AddExpression::accept(Visitor* visitor)
	{
	}
	
	Type* AddExpression::accept(TypeVisitor* visitor)
	{
	}
}
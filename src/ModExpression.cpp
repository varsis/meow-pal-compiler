#include "ModExpression.hpp"

namespace Meow
{
	ModExpression::ModExpression(Expression* left, Expression* right)
	: BinaryExpression(left, right)
	{
	}
	
	void ModExpression::accept(Visitor* visitor)
	{
	}
	
	Type* ModExpression::accept(TypeVisitor* visitor)
	{
		return 0;
	}
}



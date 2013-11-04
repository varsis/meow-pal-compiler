#include "Expression.hpp"

namespace Meow
{
	Expression::Expression()
	{
	}
	
	Expression::Expression(StringLiteral* literal)
	{
	}

	Expression::Expression(IntegerConstant* constant)
	{
	}

	Expression::Expression(RealConstant* constant)
	{
	}

	Expression::Expression(LValue* value)
	{
	}
	
	void Expression::accept(Visitor* visitor)
	{
	}
	
	Type* Expression::accept(TypeVisitor* visitor)
	{
		return 0;
	}
}

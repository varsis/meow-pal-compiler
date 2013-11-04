#include "NotExpression.hpp"

namespace Meow
{
	NotExpression::NotExpression(Expression* operand)
	: m_operand(operand)
	{
	}
	
	void NotExpression::accept(Visitor* visitor)
	{
	}
	
	Type* NotExpression::accept(TypeVisitor* visitor)
	{
		return 0;
	}
	
}

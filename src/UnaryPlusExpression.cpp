#include "UnaryPlusExpression.hpp"
namespace Meow
{
	
	UnaryPlusExpression::UnaryPlusExpression(Expression* operand)
	: m_operand(operand)
	{
	}
	
	void UnaryPlusExpression::accept(Visitor* visitor)
	{
	}
	Type* UnaryPlusExpression::accept(TypeVisitor* visitor)
	{
		return 0;
	}
}


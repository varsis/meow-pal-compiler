#include "UnaryMinusExpression.hpp"
namespace Meow
{
	UnaryMinusExpression::UnaryMinusExpression(Expression* operand)
	: m_operand(operand)
	{
	}
	
	void UnaryMinusExpression::accept(Visitor* visitor)
	{
	}
}


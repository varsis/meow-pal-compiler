#include "SimpleExpression.hpp"
#include "LValue.hpp"
#include "Visitor.hpp"

namespace Meow
{
	SimpleExpression::SimpleExpression(LValue* value)
		: m_value(value)
	{
	}

	void SimpleExpression::acceptPreOrder(Visitor* visitor)
	{
		visitor->visit(this);
		m_value->acceptPreOrder(visitor);
	}

	void SimpleExpression::acceptPostOrder(Visitor* visitor)
	{
		m_value->acceptPostOrder(visitor);
		visitor->visit(this);
	}
}

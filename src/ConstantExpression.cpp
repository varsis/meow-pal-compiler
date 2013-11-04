#include "ConstantExpression.hpp"
#include "Constant.hpp"
#include "Visitor.hpp"

namespace Meow
{
	ConstantExpression::ConstantExpression(Constant* value)
		: m_value(value)
	{
	}

	void ConstantExpression::acceptPreOrder(Visitor* visitor)
	{
		visitor->visit(this);
		m_value->acceptPreOrder(visitor);
	}

	void ConstantExpression::acceptPostOrder(Visitor* visitor)
	{
		m_value->acceptPostOrder(visitor);
		visitor->visit(this);
	}
}

#include "SubscriptedVariable.hpp"
#include "Visitor.hpp"
#include "LValue.hpp"
#include "Expression.hpp"

namespace Meow
{
	SubscriptedVariable::SubscriptedVariable(int lineNumber, LValue* var, Expression* subscript)
		: m_variable(var)
		, m_subscript(subscript)
	{
	}
	
	void SubscriptedVariable::acceptPreOrder(Visitor* visitor)
	{
		visitor->visit(this);
		m_variable->acceptPreOrder(visitor);
		m_subscript->acceptPreOrder(visitor);
	}

	void SubscriptedVariable::acceptPostOrder(Visitor* visitor)
	{
		m_variable->acceptPostOrder(visitor);
		m_subscript->acceptPostOrder(visitor);
		visitor->visit(this);
	}
}


#include "SubscriptedVariable.hpp"
namespace Meow
{
	SubscriptedVariable::SubscriptedVariable(int lineNumber, LValue* var, Expression* subscript)
	: m_variable(var)
	, m_subscript(subscript)
	{
	}
	
	void SubscriptedVariable::accept(Visitor* visitor)
	{
	}
	Type* SubscriptedVariable::accept(TypeVisitor* visitor)
	{
		return 0;
	}
	
}


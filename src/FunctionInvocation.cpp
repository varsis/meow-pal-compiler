#include "FunctionInvocation.hpp"
#include "Identifier.hpp"
#include "Arguments.hpp"
#include "Visitor.hpp"

namespace Meow
{
	
	FunctionInvocation::FunctionInvocation(Identifier* name, Arguments* a)
	: m_functionId(name)
	, m_arguments(a)
	{
	}
	
	void FunctionInvocation::acceptPreOrder(Visitor* visitor)
	{
		visitor->visit(this);
		m_functionId->acceptPreOrder(visitor);
		m_arguments->acceptPreOrder(visitor);
	}

	void FunctionInvocation::acceptPostOrder(Visitor* visitor)
	{
		m_functionId->acceptPostOrder(visitor);
		m_arguments->acceptPostOrder(visitor);
		visitor->visit(this);
	}
}

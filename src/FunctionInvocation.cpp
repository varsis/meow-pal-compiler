#include "FunctionInvocation.hpp"

namespace Meow
{
	
	FunctionInvocation::FunctionInvocation(Identifier* name, Arguments* a)
	: m_functionId(name)
	, m_arguments(a)
	{
	}
	
	void FunctionInvocation::accept(Visitor* visitor)
	{
	}
	Type* FunctionInvocation::accept(TypeVisitor* visitor)
	{
		return 0;
	}
	
}

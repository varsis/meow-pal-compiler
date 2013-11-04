#include "ProcedureInvocation.hpp"

namespace Meow
{
	ProcedureInvocation::ProcedureInvocation(Identifier* procId, Arguments* a)
	: m_procedureId(procId)
	, m_arguments(a)
	{
	}
	
	void ProcedureInvocation::accept(Visitor* visitor)
	{
	}
	
}

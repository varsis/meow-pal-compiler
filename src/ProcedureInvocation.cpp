#include "ProcedureInvocation.hpp"
#include "Visitor.hpp"
#include "Identifier.hpp"
#include "Arguments.hpp"

namespace Meow
{
	ProcedureInvocation::ProcedureInvocation(Identifier* procId, Arguments* a)
		: m_procedureId(procId)
		, m_arguments(a)
	{
	}
	
	void ProcedureInvocation::acceptPreOrder(Visitor* visitor)
	{
		visitor->visit(this);
		m_procedureId->acceptPreOrder(visitor);
		m_arguments->acceptPreOrder(visitor);
	}

	void ProcedureInvocation::acceptPostOrder(Visitor* visitor)
	{
		m_procedureId->acceptPostOrder(visitor);
		m_arguments->acceptPostOrder(visitor);
		visitor->visit(this);
	}
	
}

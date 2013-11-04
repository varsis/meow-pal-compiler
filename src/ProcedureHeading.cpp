#include "ProcedureHeading.hpp"

namespace Meow
{
	
	ProcedureHeading::ProcedureHeading(int lineNumber,
			 Identifier* identifier,
			 ParameterList* params,
			 Identifier* type)
	: m_identifier(identifier)
	, m_parameters(params)
	, m_type(type)
	{
	}
	
	void ProcedureHeading::accept(Visitor* visitor)
	{
		
	}
	
	const Identifier* ProcedureHeading::getIdentifier() const
	{
		return m_identifier;
	}
	
	const ParameterList* ProcedureHeading::getParameters() const
	{
		return m_parameters;
	}
	
	const Identifier* ProcedureHeading::getType() const
	{
		return m_type;
	}
	
}

#include "ProcedureHeading.hpp"
#include "Visitor.hpp"
#include "Identifier.hpp"
#include "ParameterList.hpp"

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
	
	void ProcedureHeading::acceptPreOrder(Visitor* visitor)
	{
		visitor->visit(this);
		m_identifier->acceptPreOrder(visitor);
		m_type->acceptPreOrder(visitor);
		m_parameters->acceptPreOrder(visitor);
	}

	void ProcedureHeading::acceptPostOrder(Visitor* visitor)
	{
		m_identifier->acceptPostOrder(visitor);
		m_type->acceptPostOrder(visitor);
		m_parameters->acceptPostOrder(visitor);
		visitor->visit(this);
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

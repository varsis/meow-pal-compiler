#include "ProcedureDeclaration.hpp"

namespace Meow
{
	
	ProcedureDeclaration::ProcedureDeclaration(int lineNumber,
			     ProcedureHeading* heading,
			     Declarations* procedureDeclarations,
			     CompoundStatement* statements)
	: m_heading(heading)
	, m_declarations(procedureDeclarations)
	, m_statements(statements)
	{
	}
	
	void ProcedureDeclaration::accept(Visitor* visitor)
	{
	}
	const Type* ProcedureDeclaration::accept(TypeVisitor* typeVisitor)
	{
	}
	
	const ProcedureHeading* ProcedureDeclaration::getHeading() const
	{
		return m_heading;
	}
	
	const Declarations* ProcedureDeclaration::getDeclarations() const
	{
		return m_declarations;
	}
}

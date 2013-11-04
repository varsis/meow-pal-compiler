#include "ProcedureDeclaration.hpp"
#include "Visitor.hpp"
#include "ProcedureHeading.hpp"
#include "Declarations.hpp"
#include "CompoundStatement.hpp"

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
	
	void ProcedureDeclaration::acceptPreOrder(Visitor* visitor)
	{
		visitor->visit(this);
		m_heading->acceptPreOrder(visitor);
		m_declarations->acceptPreOrder(visitor);
		m_statements->acceptPreOrder(visitor);
	}

	void ProcedureDeclaration::acceptPostOrder(Visitor* visitor)
	{
		m_heading->acceptPostOrder(visitor);
		m_declarations->acceptPostOrder(visitor);
		m_statements->acceptPostOrder(visitor);
		visitor->visit(this);
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

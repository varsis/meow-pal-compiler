#include "Program.hpp"
#include "Declarations.hpp"
#include "CompoundStatement.hpp"

namespace Meow
{
	Program::Program(Declarations* declarations, CompoundStatement* statements)
		: m_declarations(declarations)
		, m_statements(statements)
	{
	}

	void Program::accept(Visitor* visitor)
	{
		//m_declarations->accept(visitor);
		//m_statements->accept(visitor);
		
		visitor->visit(this);
	}

	const CompoundStatement* Program::getStatements() const
	{
		return m_statements;
	}
	
	const Declarations* Program::getDeclarations() const
	{
		return m_declarations;
	}
}

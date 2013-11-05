#include "Program.hpp"
#include "Declarations.hpp"
#include "CompoundStatement.hpp"
#include "ASTListTypes.hpp"

namespace Meow
{
	Program::Program(Declarations* declarations, CompoundStatement* statements)
		: m_declarations(declarations)
		, m_statements(statements)
	{
	}

	void Program::acceptPreOrder(Visitor* visitor)
	{
		visitor->visit(this);
		m_declarations->acceptPreOrder(visitor);
		m_statements->acceptPreOrder(visitor);
	}

	void Program::acceptPostOrder(Visitor* visitor)
	{
		m_declarations->acceptPostOrder(visitor);
		m_statements->acceptPostOrder(visitor);
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

#include "ConditionalStatement.hpp"
#include "Visitor.hpp"
#include "Expression.hpp"
#include "Statement.hpp"

namespace Meow
{
	ConditionalStatement::ConditionalStatement(Expression* condition,
						   Statement* thenStatement,
						   Statement* elseStatement)
	   : m_condition(condition)
	   , m_thenStatement(thenStatement)
	   , m_elseStatement(elseStatement)
	{
	}

	void ConditionalStatement::acceptPreOrder(Visitor* visitor)
	{
		visitor->visit(this);
		m_condition->acceptPreOrder(visitor);
		m_thenStatement->acceptPreOrder(visitor);

		if (m_elseStatement)
		{
		   m_elseStatement->acceptPreOrder(visitor);
		}
	}
	
	void ConditionalStatement::acceptPostOrder(Visitor* visitor)
	{
		m_condition->acceptPostOrder(visitor);
		m_thenStatement->acceptPostOrder(visitor);

		if (m_elseStatement)
		{
		   m_elseStatement->acceptPostOrder(visitor);
		}

		visitor->visit(this);
	}
}

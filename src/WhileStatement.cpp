#include "WhileStatement.hpp"
#include "Visitor.hpp"
#include "Expression.hpp"
#include "Statement.hpp"

namespace Meow
{
	
       WhileStatement::WhileStatement(Expression* condition, Statement* loopStatement)
	       : m_condition(condition)
	       , m_loopStatement(loopStatement)
	{
	}
	
	void WhileStatement::acceptPreOrder(Visitor* visitor)
	{
		visitor->visit(this);
		m_condition->acceptPreOrder(visitor);
		m_loopStatement->acceptPreOrder(visitor);
	}

	void WhileStatement::acceptPostOrder(Visitor* visitor)
	{
		m_condition->acceptPostOrder(visitor);
		m_loopStatement->acceptPostOrder(visitor);
		visitor->visit(this);
	}
}


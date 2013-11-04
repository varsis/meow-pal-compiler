#include "WhileStatement.hpp"

namespace Meow
{
	
       WhileStatement::WhileStatement(Expression* condition, Statement* loopStatement)
	       : m_condition(condition)
	       , m_loopStatement(loopStatement)
	{
	}
	
	void WhileStatement::accept(Visitor* visitor)
	{
	}
}


#include "ConditionalStatement.hpp"

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
	
	void ConditionalStatement::accept(Visitor* visitor)
	{
	}
	
	Type* ConditionalStatement::accept(TypeVisitor* visitor)
	{
		return 0;
	}
	
}



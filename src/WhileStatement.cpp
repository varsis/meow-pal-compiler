#include "WhileStatement.cpp"

namespace Meow
{
	
	WhileStatement(Expression* condition,
		       Statement* loopStatement)
	: m_condition(condition)
	, m_loopStatement(loopStatement)
	{
	}
	
	virtual void accept(Visitor* visitor)
	{
	}
	virtual Type* accept(TypeVisitor* visitor)
	{
		return 0;
	}
}


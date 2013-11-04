#include "AssignStatement.hpp"
#include "Visitor.hpp"
#include "LValue.hpp"
#include "Expression.hpp"

namespace Meow
{
	AssignStatement::AssignStatement(LValue* v, Expression* e)
		: m_lvalue(v)
		, m_rvalue(e)
	{
	}

	void AssignStatement::acceptPreOrder(Visitor* visitor)
	{
		visitor->visit(this);
		m_lvalue->acceptPreOrder(visitor);
		m_rvalue->acceptPreOrder(visitor);
	}

	void AssignStatement::acceptPostOrder(Visitor* visitor)
	{
		m_lvalue->acceptPostOrder(visitor);
		m_rvalue->acceptPostOrder(visitor);
		visitor->visit(this);
	}
}



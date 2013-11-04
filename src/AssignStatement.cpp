#include "AssignStatement.hpp"

namespace Meow
{
	AssignStatement::AssignStatement(LValue* v, Expression* e)
		: m_lvalue(v)
		, m_rvalue(e)
	{
	}
	
	void AssignStatement::accept(Visitor* visitor)
	{
	}
}



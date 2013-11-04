#include "Variable.hpp"
#include "Visitor.hpp"

namespace Meow
{
	Variable::Variable(int lineNumber, Identifier* id)
		: m_identifier(id)
	{
	}
	
	void Variable::acceptPreOrder(Visitor* visitor)
	{
		visitor->visit(this);
		m_identifier->acceptPreOrder(visitor);
	}

	void Variable::acceptPostOrder(Visitor* visitor)
	{
		m_identifier->acceptPostOrder(visitor);
		visitor->visit(this);
	}
}


#include "Arguments.hpp"
#include "Visitor.hpp"
#include "Expression.hpp"

namespace Meow
{
	Arguments::Arguments()
	{
	}
	
	void Arguments::addArgument(Expression* e)
	{
		m_arguments.push_back(e);
	}
	
	void Arguments::acceptPreOrder(Visitor* visitor)
	{
		visitor->visit(this);

		ExpressionList::iterator it;
		for (it = m_arguments.begin(); it != m_arguments.end(); ++it)
		{
			(*it)->acceptPreOrder(visitor);
		}
	}

	void Arguments::acceptPostOrder(Visitor* visitor)
	{
		ExpressionList::iterator it;
		for (it = m_arguments.begin(); it != m_arguments.end(); ++it)
		{
			(*it)->acceptPostOrder(visitor);
		}

		visitor->visit(this);
	}
}

#include "ContinueStatement.hpp"
#include "Visitor.hpp"

namespace Meow
{
	void ContinueStatement::acceptPreOrder(Visitor* visitor)
	{
		visitor->visit(this);
	}

	void ContinueStatement::acceptPostOrder(Visitor* visitor)
	{
		visitor->visit(this);
	}
}


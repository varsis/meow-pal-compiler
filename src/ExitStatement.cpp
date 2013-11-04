#include "ExitStatement.hpp"
#include "Visitor.hpp"

namespace Meow
{
	void ExitStatement::acceptPreOrder(Visitor* visitor)
	{
		visitor->visit(this);
	}

	void ExitStatement::acceptPostOrder(Visitor* visitor)
	{
		visitor->visit(this);
	}
}


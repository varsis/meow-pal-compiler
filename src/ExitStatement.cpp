#include "ExitStatement.hpp"

namespace Meow
{
	
	void ExitStatement::accept(Visitor* visitor)
	{
	}
	
	Type* ExitStatement::accept(TypeVisitor* visitor)
	{
		return 0;
	}
	
}


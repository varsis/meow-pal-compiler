#include "Statement.hpp"

namespace Meow
{
	
	void Statement::accept(Visitor* visitor)
	{
	}
	Type* Statement::accept(TypeVisitor* visitor)
	{
		return 0;
	}
}


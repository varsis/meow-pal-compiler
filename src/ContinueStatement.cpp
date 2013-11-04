#include "ContinueStatement.hpp"

namespace Meow
{
	
	void ContinueStatement::accept(Visitor* visitor)
	{
	}
	
	Type* ContinueStatement::accept(TypeVisitor* visitor)
	{
		return 0;
	}
}


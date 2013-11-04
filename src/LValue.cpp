#include "LValue.hpp"

namespace Meow
{
	
	void LValue::accept(Visitor* visitor)
	{
	}
	Type* LValue::accept(TypeVisitor* visitor)
	{
		return 0;
	}
}

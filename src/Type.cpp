\#include "Type.hpp"

// Forward Declarations
namespace Meow
{
	
	void Type::accept(Visitor* visitor)
	{
	}
	Type* Type::accept(TypeVisitor* visitor)
	{
		return 0;
	}
}

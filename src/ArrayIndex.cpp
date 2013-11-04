#include "ArrayIndex.hpp"

namespace Meow
{
	
	void ArrayIndex::accept(Visitor* visitor)
	{
	}
    
	Type * ArrayIndex::accept (TypeVisitor* visitor)
	{
	    return 0;
	}
}
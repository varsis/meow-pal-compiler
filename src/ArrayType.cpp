#include "ArrayType.hpp"

// Forward Declarations
namespace Meow
{
	ArrayType::ArrayType(ArrayIndex* index, Type* elementType)
	{
	}
	
	void ArrayType::accept(Visitor* visitor)
	{
	}
	
	Type* ArrayType::accept(TypeVisitor* visitor)
	{
		return 0;
	}
	
}


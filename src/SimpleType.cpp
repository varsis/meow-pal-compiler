#include "SimpleType.hpp"

// Forward Declarations
namespace Meow
{
	SimpleType::SimpleType(Identifier* name)
	: m_name(name)
	{
	}
	
	void SimpleType::accept(Visitor* visitor)
	{
	}
}


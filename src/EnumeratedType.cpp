#include "EnumeratedType.hpp"

// Forward Declarations
namespace Meow
{
	EnumeratedType::EnumeratedType(IdentifierList* entries)
	: m_entries(entries)
	{
	}
	
	void EnumeratedType::accept(Visitor* visitor)
	{
	}
}


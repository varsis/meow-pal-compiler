#include "IdentifierType.hpp"

namespace Meow
{
	
	IdentifierType::IdentifierType(unsigned int lineNumber, const char* identiferTypeName)
	{
	}
	
	void IdentifierType::accept(Visitor * visitor)
	{
	}
	
	Type* IdentifierType::accept(TypeVisitor * typeVisitor)
	{
	}
	
	std::string IdentifierType::toString() const
	{
	}
	
}

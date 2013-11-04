#include "Identifier.hpp"

namespace Meow
{
	Identifier::Identifier(int lineNumber, const char* name)
		: m_name(name)
	{
		//setLineNumber(lineNumber);
	}
	
	std::string Identifier::toString() const
	{
		return m_name;
	}
}

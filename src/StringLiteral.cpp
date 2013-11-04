#include "StringLiteral.hpp"

namespace Meow
{
	StringLiteral::StringLiteral(int lineNumber, char* value)
		: m_value(value)
	{
	}

	std::string StringLiteral::getValue()
	{
		return m_value;
	}
}

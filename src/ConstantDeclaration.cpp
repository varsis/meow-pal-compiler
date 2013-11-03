#include "ConstantDeclaration.hpp"
#include "Identifier.hpp"

namespace Meow
{
	ConstantDeclaration::ConstantDeclaration(int lineNumber,
						Identifier* identifier,
						Expression* expression)
		: m_identifier(identifier)
	{
	}
}


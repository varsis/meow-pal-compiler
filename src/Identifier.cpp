#include "Identifier.hpp"
#include "Visitor.hpp"

namespace Meow
{
	Identifier::Identifier(int lineNumber, const char* name)
		: m_name(name)
	{
		//setLineNumber(lineNumber);
	}

	void Identifier::acceptPreOrder(Visitor* visitor)
	{
		visitor->visit(this);
	}

	void Identifier::acceptPostOrder(Visitor* visitor)
	{
		visitor->visit(this);
	}
	
	std::string Identifier::toString() const
	{
		return m_name;
	}
}

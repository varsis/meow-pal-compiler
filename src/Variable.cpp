#include "Variable.hpp"

namespace Meow
{
	Variable::Variable(int lineNumber, Identifier* id)
		: m_identifier(id)
	{
	}
	
	void Variable::accept(Visitor* visitor)
	{
	}
}


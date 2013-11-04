#include "Variable.hpp"

namespace Meow
{
	
	Variable(int lineNumber, Identifier* id)
	: m_identifier(id)
	{
	}
	
	virtual void accept(Visitor* visitor)
	{
	}
	
	virtual Type* accept(TypeVisitor* visitor)
	{
		return 0;
	}
}


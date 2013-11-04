#include "Arguments.hpp"

namespace Meow
{
	Arguments::Arguments()
	{
	}
	
	void Arguments::addArgument(Expression* e)
	{
		m_arguments.push_back(e);
	}
	
	void Arguments::accept(Visitor* visitor)
	{
	}
	
	Type* Arguments::accept(TypeVisitor* visitor)
	{
		return 0;
	}
}

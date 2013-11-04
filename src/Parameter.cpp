#include "Parameter.hpp"

namespace Meow
{
	
	Parameter::Parameter(int lineNumber, Identifier* name, Identifier* type, bool varParam)
	: m_name(name)
	, m_type(type)
	, m_varParam(varParam)
	{
	}
	
	Identifier* Parameter::getName()
	{
		return m_name;
	}
	
	Identifier* Parameter::getType()
	{
		return m_type;
	}
	
	void Parameter::accept(Visitor* visitor)
	{
	}
	
	const Type* Parameter::accept(TypeVisitor* typeVisitor)
	{
	}
	
}

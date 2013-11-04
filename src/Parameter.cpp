#include "Parameter.hpp"
#include "Visitor.hpp"
#include "Identifier.hpp"

namespace Meow
{
	
	Parameter::Parameter(int lineNumber, Identifier* name, Identifier* type, bool varParam)
		: m_name(name)
		, m_type(type)
		, m_varParam(varParam)
	{
	}

	void Parameter::acceptPreOrder(Visitor* visitor)
	{
		visitor->visit(this);
		m_name->acceptPreOrder(visitor);
		m_type->acceptPreOrder(visitor);
	}

	void Parameter::acceptPostOrder(Visitor* visitor)
	{
		m_name->acceptPostOrder(visitor);
		m_type->acceptPostOrder(visitor);
		visitor->visit(this);
	}
	
	Identifier* Parameter::getName()
	{
		return m_name;
	}
	
	Identifier* Parameter::getType()
	{
		return m_type;
	}
}

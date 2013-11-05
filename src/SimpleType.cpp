#include "SimpleType.hpp"
#include "Visitor.hpp"
#include "Identifier.hpp"
#include "Expression.hpp"

namespace Meow
{
	SimpleType::SimpleType(Identifier* name)
		: m_name(name)
	{
	}
	
	void SimpleType::acceptPreOrder(Visitor* visitor)
	{
		visitor->visit(this);
		m_name->acceptPreOrder(visitor);
	}

	void SimpleType::acceptPostOrder(Visitor* visitor)
	{
		m_name->acceptPostOrder(visitor);
		visitor->visit(this);
	}
}


#include "ArrayTypeIndex.hpp"
#include "Visitor.hpp"
#include "Type.hpp"

namespace Meow
{
	
	ArrayTypeIndex::ArrayTypeIndex(Type* indexType)
		: m_type(indexType)
	{
	}
	
	void ArrayTypeIndex::acceptPreOrder(Visitor* visitor)
	{
		visitor->visit(this);
		m_type->acceptPreOrder(visitor);
	}

	void ArrayTypeIndex::acceptPostOrder(Visitor* visitor)
	{
		m_type->acceptPostOrder(visitor);
		visitor->visit(this);
	}
}

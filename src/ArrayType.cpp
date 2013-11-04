#include "ArrayType.hpp"
#include "Visitor.hpp"
#include "ArrayIndex.hpp"
#include "Type.hpp"

// Forward Declarations
namespace Meow
{
	ArrayType::ArrayType(ArrayIndex* index, Type* elementType)
		: m_index(index)
		, m_elementType(elementType)
	{
	}
	
	void ArrayType::acceptPreOrder(Visitor* visitor)
	{
		visitor->visit(this);
		m_index->acceptPreOrder(visitor);
		m_elementType->acceptPreOrder(visitor);
	}

	void ArrayType::acceptPostOrder(Visitor* visitor)
	{
		m_index->acceptPostOrder(visitor);
		m_elementType->acceptPostOrder(visitor);
		visitor->visit(this);
	}
}


#include "ArrayTypeIndex.hpp"
namespace Meow
{
	
	ArrayTypeIndex::ArrayTypeIndex(Type* indexType)
		: m_type(indexType)
	{
	}
	
	void ArrayTypeIndex::accept(Visitor* visitor)
	{
	}
}

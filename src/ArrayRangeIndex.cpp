#include "ArrayRangeIndex.hpp"
namespace Meow
{
	ArrayRangeIndex::ArrayRangeIndex(Expression* start, Expression* end)
		: m_start(start)
		, m_end(end)
	{
	}
	
	void ArrayRangeIndex::accept(Visitor* visitor)
	{
	}
	Type* ArrayRangeIndex::accept(TypeVisitor* visitor)
	{
		return 0;
	}
	
}


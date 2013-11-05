#include "ArrayRangeIndex.hpp"
#include "Visitor.hpp"
#include "Expression.hpp"

namespace Meow
{
	ArrayRangeIndex::ArrayRangeIndex(Expression* start, Expression* end)
		: m_start(start)
		, m_end(end)
	{
	}
	
	void ArrayRangeIndex::acceptPreOrder(Visitor* visitor)
	{
		visitor->visit(this);
		m_start->acceptPreOrder(visitor);
		m_end->acceptPreOrder(visitor);
	}

	void ArrayRangeIndex::acceptPostOrder(Visitor* visitor)
	{
		m_start->acceptPostOrder(visitor);
		m_end->acceptPostOrder(visitor);
		visitor->visit(this);
	}
}

#ifndef ARRAYRANGEINDEX_HPP
#define ARRAYRANGEINDEX_HPP

#include "ASTListTypes.hpp"
#include "ArrayIndex.hpp"

// Forward Declarations
namespace Meow
{
	class Visitor;
	class TypeVisitor;
	class Identifier;
	class Type;

	class ArrayRangeIndex : public ArrayIndex
	{
		public:
			ArrayRangeIndex(Expression* start, Expression* end)
				: m_start(start)
				, m_end(end)
			{
			}

			virtual void accept(Visitor* visitor) { }
			virtual Type* accept(TypeVisitor* visitor) {return 0;}

		private:
			Expression* m_start;
			Expression* m_end;
	};
}

#endif

#ifndef ARRAYRANGEINDEX_HPP
#define ARRAYRANGEINDEX_HPP

#include "ASTListTypes.hpp"
#include "ArrayIndex.hpp"

// Forward Declarations
namespace Meow
{
	class Visitor;
	class Identifier;
	class Type;

	class ArrayRangeIndex : public ArrayIndex
	{
		public:
			ArrayRangeIndex(Expression* start, Expression* end);

			virtual void accept(Visitor* visitor);

		private:
			Expression* m_start;
			Expression* m_end;
	};
}

#endif

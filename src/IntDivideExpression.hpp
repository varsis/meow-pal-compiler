#ifndef INTDIVIDEEXPRESSION_HPP
#define INTDIVIDEEXPRESSION_HPP

#include "BinaryExpression.hpp"

namespace Meow
{
	// Forward Declarations
	class Visitor;
	class TypeVisitor;
	class Type;

	class IntDivideExpression : public BinaryExpression
	{
		public:
			IntDivideExpression(Expression* left, Expression* right)
				: BinaryExpression(left, right)
			{
			}

			virtual void accept(Visitor* visitor) { }
			virtual Type* accept(TypeVisitor* visitor) {return 0;}

	};
}

#endif


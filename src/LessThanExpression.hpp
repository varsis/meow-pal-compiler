#ifndef LESSTHANEXPRESSION_HPP
#define LESSTHANEXPRESSION_HPP

#include "BinaryExpression.hpp"

namespace Meow
{
	// Forward Declarations
	class Visitor;
	class TypeVisitor;
	class Type;

	class LessThanExpression : public BinaryExpression
	{
		public:
			LessThanExpression(Expression* left, Expression* right)
				: BinaryExpression(left, right)
			{
			}

			virtual void accept(Visitor* visitor) { }
			virtual Type* accept(TypeVisitor* visitor) {return 0;}

	};
}

#endif

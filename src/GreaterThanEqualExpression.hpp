#ifndef GREATERTHANEQUALEXPRESSION_HPP
#define GREATERTHANEQUALEXPRESSION_HPP

#include "BinaryExpression.hpp"

namespace Meow
{
	// Forward Declarations
	class Visitor;
	class TypeVisitor;
	class Type;

	class GreaterThanEqualExpression : public BinaryExpression
	{
		public:
			GreaterThanEqualExpression(Expression* left, Expression* right)
				: BinaryExpression(left, right)
			{
			}

			virtual void accept(Visitor* visitor) { }
			virtual Type* accept(TypeVisitor* visitor) {return 0;}

	};
}

#endif

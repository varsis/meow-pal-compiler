#ifndef SUBTRACTEXPRESSION_HPP
#define SUBTRACTEXPRESSION_HPP

#include "BinaryExpression.hpp"

namespace Meow
{
	// Forward Declarations
	class Visitor;
	class TypeVisitor;
	class Type;

	class SubtractExpression : public BinaryExpression
	{
		public:
			SubtractExpression(Expression* left, Expression* right)
				: BinaryExpression(left, right)
			{
			}

			virtual void accept(Visitor* visitor) { }
			virtual Type* accept(TypeVisitor* visitor) {return 0;}

	};
}

#endif

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
			LessThanExpression(Expression* left, Expression* right);

			virtual void accept(Visitor* visitor);
			virtual Type* accept(TypeVisitor* visitor);

	};
}

#endif

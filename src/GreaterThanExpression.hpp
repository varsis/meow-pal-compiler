#ifndef GREATERTHANEXPRESSION_HPP
#define GREATERTHANEXPRESSION_HPP

#include "BinaryExpression.hpp"

namespace Meow
{
	// Forward Declarations
	class Visitor;
	class TypeVisitor;
	class Type;

	class GreaterThanExpression : public BinaryExpression
	{
		public:
			GreaterThanExpression(Expression* left, Expression* right);
			virtual void accept(Visitor* visitor);
			virtual Type* accept(TypeVisitor* visitor);

	};
}

#endif

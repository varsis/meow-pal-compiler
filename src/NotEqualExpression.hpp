#ifndef NOTEQUALEXPRESSION_HPP
#define NOTEQUALEXPRESSION_HPP

#include "BinaryExpression.hpp"

namespace Meow
{
	// Forward Declarations
	class Visitor;
	class TypeVisitor;
	class Type;

	class NotEqualExpression : public BinaryExpression
	{
		public:
			NotEqualExpression(Expression* left, Expression* right);
			virtual void accept(Visitor* visitor);
			virtual Type* accept(TypeVisitor* visitor);

	};
}

#endif

#ifndef EQUALEXPRESSION_HPP
#define EQUALEXPRESSION_HPP

#include "BinaryExpression.hpp"

namespace Meow
{
	// Forward Declarations
	class Visitor;
	class TypeVisitor;
	class Type;

	class EqualExpression : public BinaryExpression
	{
		public:
			EqualExpression(Expression* left, Expression* right);

			virtual void accept(Visitor* visitor);
			virtual Type* accept(TypeVisitor* visitor);
	};
}

#endif

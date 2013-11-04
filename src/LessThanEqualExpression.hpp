#ifndef LESSTHANEQUALEXPRESSION_HPP
#define LESSTHANEQUALEXPRESSION_HPP

#include "BinaryExpression.hpp"

namespace Meow
{
	// Forward Declarations
	class Visitor;
	class TypeVisitor;
	class Type;

	class LessThanEqualExpression : public BinaryExpression
	{
		public:
		LessThanEqualExpression(Expression* left, Expression* right);

		void accept(Visitor* visitor);
		Type* accept(TypeVisitor* visitor);

	};
}

#endif

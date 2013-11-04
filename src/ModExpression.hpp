#ifndef MODEXPRESSION_HPP
#define MODEXPRESSION_HPP

#include "BinaryExpression.hpp"

namespace Meow
{
	// Forward Declarations
	class Visitor;
	class TypeVisitor;
	class Type;

	class ModExpression : public BinaryExpression
	{
		public:
			ModExpression(Expression* left, Expression* right);

			virtual void accept(Visitor* visitor);
			virtual Type* accept(TypeVisitor* visitor);

	};
}

#endif


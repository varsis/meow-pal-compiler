#ifndef GREATERTHANEQUALEXPRESSION_HPP
#define GREATERTHANEQUALEXPRESSION_HPP

#include "BinaryExpression.hpp"

namespace Meow
{
	// Forward Declarations
	class Visitor;
	class Type;

	class GreaterThanEqualExpression : public BinaryExpression
	{
		public:
			GreaterThanEqualExpression(Expression* left, Expression* right);

			virtual void accept(Visitor* visitor);

	};
}

#endif

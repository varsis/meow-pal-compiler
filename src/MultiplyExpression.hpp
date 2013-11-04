#ifndef MULTIPLYEXPRESSION_HPP
#define MULTIPLYEXPRESSION_HPP

#include "BinaryExpression.hpp"

namespace Meow
{
	// Forward Declarations
	class Visitor;
	class Type;

	class MultiplyExpression : public BinaryExpression
	{
		public:
			MultiplyExpression(Expression* left, Expression* right);
			virtual void accept(Visitor* visitor);

	};
}

#endif

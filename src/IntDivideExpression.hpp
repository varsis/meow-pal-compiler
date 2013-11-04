#ifndef INTDIVIDEEXPRESSION_HPP
#define INTDIVIDEEXPRESSION_HPP

#include "BinaryExpression.hpp"

namespace Meow
{
	// Forward Declarations
	class Visitor;
	class Type;

	class IntDivideExpression : public BinaryExpression
	{
		public:
			IntDivideExpression(Expression* left, Expression* right);

			virtual void accept(Visitor* visitor);

	};
}

#endif


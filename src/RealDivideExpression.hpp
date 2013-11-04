#ifndef REALDIVIDEEXPRESSION_HPP
#define REALDIVIDEEXPRESSION_HPP

#include "BinaryExpression.hpp"

namespace Meow
{
	// Forward Declarations
	class Visitor;
	class Type;

	class RealDivideExpression : public BinaryExpression
	{
		public:
			RealDivideExpression(Expression* left, Expression* right);

			virtual void accept(Visitor* visitor);

	};
}

#endif

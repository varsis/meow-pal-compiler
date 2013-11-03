#ifndef REALDIVIDEEXPRESSION_HPP
#define REALDIVIDEEXPRESSION_HPP

#include "BinaryExpression.hpp"

namespace Meow
{
	// Forward Declarations
	class Visitor;
	class TypeVisitor;
	class Type;

	class RealDivideExpression : public BinaryExpression
	{
		public:
			RealDivideExpression(Expression* left, Expression* right)
				: BinaryExpression(left, right)
			{
			}

			virtual void accept(Visitor* visitor) { }
			virtual Type* accept(TypeVisitor* visitor) {return 0;}

	};
}

#endif

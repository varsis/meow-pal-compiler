#ifndef UNARYPLUSEXPRESSION_HPP
#define UNARYPLUSEXPRESSION_HPP

#include "Expression.hpp"

namespace Meow
{
	// Forward Declarations
	class Visitor;
	class Type;

	class UnaryPlusExpression : public Expression
	{
		public:
			UnaryPlusExpression(Expression* operand);

			virtual void acceptPreOrder(Visitor* visitor);
			virtual void acceptPostOrder(Visitor* visitor);

		protected: 
			Expression* m_operand;

	};
}

#endif

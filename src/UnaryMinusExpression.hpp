#ifndef UNARYMINUSEXPRESSION_HPP
#define UNARYMINUSEXPRESSION_HPP

#include "Expression.hpp"

namespace Meow
{
	// Forward Declarations
	class Visitor;
	class Type;

	class UnaryMinusExpression : public Expression
	{
		public:
			UnaryMinusExpression(Expression* operand);

			virtual void acceptPreOrder(Visitor* visitor);
			virtual void acceptPostOrder(Visitor* visitor);
		protected: 
			Expression* m_operand;

	};
}

#endif

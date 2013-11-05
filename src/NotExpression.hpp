#ifndef NOTEXPRESSION_HPP
#define NOTEXPRESSION_HPP

#include "Expression.hpp"

namespace Meow
{
	// Forward Declarations
	class Visitor;
	class Type;

	class NotExpression : public Expression
	{
		public:
			NotExpression(Expression* operand); 

			virtual void acceptPreOrder(Visitor* visitor);
			virtual void acceptPostOrder(Visitor* visitor);

		protected: 
			Expression* m_operand;

	};
}

#endif

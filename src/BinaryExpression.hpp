#ifndef BINARYEXPRESSION_HPP
#define BINARYEXPRESSION_HPP

#include "Expression.hpp"

namespace Meow
{
	// Forward Declarations
	class Visitor;
	class Type;

	class BinaryExpression : public Expression
	{
		public:
			BinaryExpression(Expression* left, Expression* right);
			virtual void acceptPreOrder(Visitor* visitor);
			virtual void acceptPostOrder(Visitor* visitor);

		protected: 
			Expression* m_left;
			Expression* m_right;

	};
}

#endif

#ifndef BINARYEXPRESSION_HPP
#define BINARYEXPRESSION_HPP

#include "Expression.hpp"

namespace Meow
{
	// Forward Declarations
	class Visitor;
	class TypeVisitor;
	class Type;

	class BinaryExpression : public Expression
	{
		public:
			BinaryExpression(Expression* left, Expression* right);
			virtual void accept(Visitor* visitor);
			virtual Type* accept(TypeVisitor* visitor);

		protected: 
			Expression* m_left;
			Expression* m_right;

	};
}

#endif

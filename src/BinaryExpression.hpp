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
			BinaryExpression(Expression* left, Expression* right)
				: m_left(left)
				, m_right(right)
			{
			}

			virtual void accept(Visitor* visitor) { }
			virtual Type* accept(TypeVisitor* visitor) {return 0;}

		protected: 
			Expression* m_left;
			Expression* m_right;

	};
}

#endif

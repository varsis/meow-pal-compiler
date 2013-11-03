#ifndef UNARYPLUSEXPRESSION_HPP
#define UNARYPLUSEXPRESSION_HPP

#include "Expression.hpp"

namespace Meow
{
	// Forward Declarations
	class Visitor;
	class TypeVisitor;
	class Type;

	class UnaryPlusExpression : public Expression
	{
		public:
			UnaryPlusExpression(Expression* operand)
				: m_operand(operand)
			{
			}

			virtual void accept(Visitor* visitor) { }
			virtual Type* accept(TypeVisitor* visitor) {return 0;}

		protected: 
			Expression* m_operand;

	};
}

#endif

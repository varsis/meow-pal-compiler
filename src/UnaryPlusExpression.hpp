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
			UnaryPlusExpression(Expression* operand);

			virtual void accept(Visitor* visitor);
			virtual Type* accept(TypeVisitor* visitor);

		protected: 
			Expression* m_operand;

	};
}

#endif

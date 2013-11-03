#ifndef NOTEXPRESSION_HPP
#define NOTEXPRESSION_HPP

#include "Expression.hpp"

namespace Meow
{
	// Forward Declarations
	class Visitor;
	class TypeVisitor;
	class Type;

	class NotExpression : public Expression
	{
		public:
			NotExpression(Expression* operand)
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

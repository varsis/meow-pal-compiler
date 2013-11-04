#ifndef SIMPLEEXPRESSION_HPP
#define  SIMPLEEXPRESSION_HPP

#include "Expression.hpp"

namespace Meow
{
	class Visitor;
	class Constant;

	class SimpleExpression : public Expression
	{
		public:
			SimpleExpression(LValue* value);

			virtual void acceptPreOrder(Visitor* visitor);
			virtual void acceptPostOrder(Visitor* visitor);

		private:
			LValue* m_value;
	};
}

#endif

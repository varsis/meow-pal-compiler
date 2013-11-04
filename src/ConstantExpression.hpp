#ifndef CONSTANTEXPRESSION_HPP
#define CONSTANTEXPRESSION_HPP

#include "Expression.hpp"

namespace Meow
{
	class Visitor;
	class Constant;

	class ConstantExpression : public Expression
	{
		public:
			ConstantExpression(Constant* value);

			virtual void acceptPreOrder(Visitor* visitor);
			virtual void acceptPostOrder(Visitor* visitor);

		private:
			Constant* m_value;
	};
}

#endif

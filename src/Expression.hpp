#ifndef EXPRESSION_H
#define EXPRESSION_H

#include <string>
#include "ASTNode.hpp"

namespace Meow
{
	class Visitor;
	class Type;
	class StringLiteral;
	class IntegerConstant;
	class RealConstant;
	class LValue;

	class Expression : public ASTNode
	{
		public:
			virtual void acceptPreOrder(Visitor* visitor) = 0;
			virtual void acceptPostOrder(Visitor* visitor) = 0;
	};
}

#endif

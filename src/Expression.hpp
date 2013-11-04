#ifndef EXPRESSION_H
#define EXPRESSION_H

#include <string>

namespace Meow
{
	class Visitor;
	class TypeVisitor;
	class Type;
	class StringLiteral;
	class IntegerConstant;
	class RealConstant;
	class LValue;

	class Expression
	{
		public:
			Expression();

			// FIXME this probably should be left abstract...
			// make new subclass for literals?

			Expression(StringLiteral* literal);
			Expression(IntegerConstant* constant);
			Expression(RealConstant* constant);
			Expression(LValue* value);

			virtual void accept(Visitor* visitor);
			virtual Type* accept(TypeVisitor* visitor);
	};
}

#endif

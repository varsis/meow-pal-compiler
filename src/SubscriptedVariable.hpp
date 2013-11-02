#ifndef SUBSCRIPTEDVARIABLE_HPP
#define SUBSCRIPTEDVARIABLE_HPP

#include "Identifier.hpp"
#include "Variable.hpp"
#include "ASTNode.hpp"
#include "LValue.hpp"
#include "Expression.hpp"

namespace Meow
{
	// Forward Declarations
	class Visitor;
	class TypeVisitor;
	class Type;

	class SubscriptedVariable : public LValue
	{
		public:
			SubscriptedVariable(int lineNumber, Variable* var, Expression* subscript);

			virtual void accept(Visitor visitor) = 0;
			virtual Type accept(TypeVisitor visitor) = 0;

	};
}

#endif

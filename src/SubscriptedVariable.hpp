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
	class Type;

	class SubscriptedVariable : public LValue
	{
		public:
			SubscriptedVariable(int lineNumber, LValue* var, Expression* subscript);

			virtual void acceptPreOrder(Visitor* visitor);
			virtual void acceptPostOrder(Visitor* visitor);

		private: 
			LValue* m_variable;
			Expression* m_subscript;
	};
}

#endif

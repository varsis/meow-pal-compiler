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
			SubscriptedVariable(int lineNumber, LValue* var, Expression* subscript)
				: m_variable(var)
				, m_subscript(subscript)
			{
			}

			virtual void accept(Visitor* visitor) { }
			virtual Type* accept(TypeVisitor* visitor) {return 0;}

		private: 
			LValue* m_variable;
			Expression* m_subscript;
	};
}

#endif

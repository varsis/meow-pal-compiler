#ifndef ASSIGNSTATEMENT_HPP
#define ASSIGNSTATEMENT_HPP

#include "Statement.hpp"
#include "Expression.hpp"
#include "LValue.hpp"
#include "ASTNode.hpp"

namespace Meow
{
	// Forward Declarations
	class Visitor;
	class Type;

	class AssignStatement : public Statement
	{
		public:
			AssignStatement(LValue* v, Expression* e);

			virtual void accept(Visitor* visitor);

		private:
			LValue* m_lvalue;
			Expression* m_rvalue;
	};
}

#endif

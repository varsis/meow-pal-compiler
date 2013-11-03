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
	class TypeVisitor;
	class Type;

	class AssignStatement : public Statement
	{
		public:
			AssignStatement(LValue* v, Expression* e)
				: m_lvalue(v)
				, m_rvalue(e)
			{
			}

			virtual void accept(Visitor* visitor) { }
			virtual Type* accept(TypeVisitor* visitor) {return 0;}


		private:
			LValue* m_lvalue;
			Expression* m_rvalue;
	};
}

#endif

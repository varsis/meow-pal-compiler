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
			AssignStatement(LValue v, Expression e);

			virtual void accept(Visitor visitor) = 0;
			virtual Type accept(TypeVisitor visitor) = 0;

	};
}

#endif

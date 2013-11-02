#ifndef CONDITIONALSTATEMENT_HPP
#define CONDITIONALSTATEMENT_HPP

#include "Statement.hpp"

namespace Meow
{
	// Forward Declarations
	class Visitor;
	class TypeVisitor;
	class Expression;
	class Type;

	class ConditionalStatement : public Statement
	{
		public:
			ConditionalStatement(Expression* condition,
					Statement* thenStatment,
					Statement* elseStatement);

			virtual void accept(Visitor visitor) = 0;
			virtual Type accept(TypeVisitor visitor) = 0;

	};
}

#endif

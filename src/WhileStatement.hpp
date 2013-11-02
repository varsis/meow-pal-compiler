#ifndef WHILESTATEMENT_HPP
#define WHILESTATEMENT_HPP

#include "Statement.hpp"

namespace Meow
{
	// Forward Declarations
	class Visitor;
	class TypeVisitor;
	class Expression;
	class Type;

	class WhileStatement : public Statement
	{
		public:
			WhileStatement(Expression* condition,
					Statement* loopStatement);

			virtual void accept(Visitor visitor) = 0;
			virtual Type accept(TypeVisitor visitor) = 0;

	};
}

#endif

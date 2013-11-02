#ifndef EXIT_STATEMENT_HPP
#define EXIT_STATEMENT_HPP

#include "Statement.hpp"

namespace Meow
{
	// Forward Declarations
	class Visitor;
	class TypeVisitor;
	class Type;

	class ExitStatement : public Statement
	{
		public:
			ExitStatement();

			virtual void accept(Visitor visitor) = 0;
			virtual Type accept(TypeVisitor visitor) = 0;

	};
}

#endif

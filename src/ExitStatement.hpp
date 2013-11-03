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
			virtual void accept(Visitor* visitor) { }
			virtual Type* accept(TypeVisitor* visitor) {return 0;}

	};
}

#endif

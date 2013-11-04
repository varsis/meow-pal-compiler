#ifndef EXIT_STATEMENT_HPP
#define EXIT_STATEMENT_HPP

#include "Statement.hpp"

namespace Meow
{
	// Forward Declarations
	class Visitor;
	class Type;

	class ExitStatement : public Statement
	{
		public:
			virtual void accept(Visitor* visitor);
	};
}

#endif

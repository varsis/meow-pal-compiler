#ifndef CONTINUESTATEMENT_HPP
#define CONTINUESTATEMENT_HPP

#include "Statement.hpp"

namespace Meow
{
	// Forward Declarations
	class Visitor;
	class Type;

	class ContinueStatement : public Statement
	{
		public:
			virtual void accept(Visitor* visitor);
	};
}

#endif

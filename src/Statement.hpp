#ifndef STATEMENT_HPP
#define STATEMENT_HPP

#include "ASTNode.hpp"

namespace Meow
{
	// Forward Declarations
	class Visitor;
	class Type;

	class Statement : public ASTNode
	{
		public:
			virtual void accept(Visitor* visitor);
	};
}

#endif

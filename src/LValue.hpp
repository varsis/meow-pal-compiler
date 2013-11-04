#ifndef LVALUE_HPP
#define LVALUE_HPP

#include "Identifier.hpp"
#include "ASTNode.hpp"

namespace Meow
{
	// Forward Declarations
	class Visitor;
	class Type;

	class LValue : public ASTNode
	{
		public:
			virtual void accept(Visitor* visitor);

	};
}

#endif

#ifndef TYPE_HPP
#define TYPE_HPP

#include "ASTNode.hpp"

// Forward Declarations
namespace Meow
{
	class Visitor;

	class Type : public ASTNode
	{
		public:
			virtual void accept(Visitor* visitor);
	};
}

#endif

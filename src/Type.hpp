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
			virtual void acceptPreOrder(Visitor* visitor) = 0;
			virtual void acceptPostOrder(Visitor* visitor) = 0;
	};
}

#endif

#ifndef CONSTANT_HPP
#define CONSTANT_HPP

#include "ASTNode.hpp"

namespace Meow
{
	class Constant : public ASTNode
	{
		public:
			virtual void acceptPreOrder(Visitor* visitor);
			virtual void acceptPostOrder(Visitor* visitor);
	};
}

#endif

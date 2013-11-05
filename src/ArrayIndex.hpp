#ifndef ARRAYINDEX_HPP
#define ARRAYINDEX_HPP

#include "ASTListTypes.hpp"
#include "Type.hpp"

// Forward Declarations
namespace Meow
{
	class Visitor;
	class Identifier;

	class ArrayIndex : public ASTNode
	{
		public:
			virtual void acceptPreOrder(Visitor* visitor) = 0;
			virtual void acceptPostOrder(Visitor* visitor) = 0;

		private:
	};
}

#endif

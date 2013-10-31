#ifndef TYPE_HPP
#define TYPE_HPP

#include "ASTNode.hpp"

// Forward Declarations
namespace Meow
{
	class Visitor;
	class TypeVisitor;

	class Type : public ASTNode
	{
		public:
			virtual void accept(Visitor visitor) = 0;
			virtual Type* accept(TypeVisitor visitor) = 0;
	};
}

#endif

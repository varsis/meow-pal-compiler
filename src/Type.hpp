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
			virtual void accept(Visitor* visitor) { };
			virtual Type* accept(TypeVisitor* visitor) {return 0;}
	};
}

#endif

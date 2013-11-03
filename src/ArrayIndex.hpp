#ifndef ARRAYINDEX_HPP
#define ARRAYINDEX_HPP

#include "ASTListTypes.hpp"
#include "Type.hpp"

// Forward Declarations
namespace Meow
{
	class Visitor;
	class TypeVisitor;
	class Identifier;

	class ArrayIndex : public ASTNode
	{
		public:
			virtual void accept(Visitor* visitor) { }
			virtual Type* accept(TypeVisitor* visitor) {return 0;}

		private:
	};
}

#endif

#ifndef ARRAYTYPE_HPP
#define ARRAYTYPE_HPP

#include "ASTListTypes.hpp"
#include "Type.hpp"

// Forward Declarations
namespace Meow
{
	class Visitor;
	class Identifier;
	class ArrayIndex;

	class ArrayType : public Type
	{
		public:
			ArrayType(ArrayIndex* index, Type* elementType);

			virtual void acceptPreOrder(Visitor* visitor);
			virtual void acceptPostOrder(Visitor* visitor);

		private:
			ArrayIndex* m_index;
			Type* m_elementType;
	};
}

#endif

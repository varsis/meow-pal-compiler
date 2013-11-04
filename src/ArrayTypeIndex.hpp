#ifndef ARRAYTYPEINDEX_HPP
#define ARRAYTYPEINDEX_HPP

#include "ASTListTypes.hpp"
#include "ArrayIndex.hpp"

// Forward Declarations
namespace Meow
{
	class Visitor;
	class Identifier;
	class Type;

	class ArrayTypeIndex : public ArrayIndex
	{
		public:
			ArrayTypeIndex(Type* indexType);

			virtual void accept(Visitor* visitor);

		private:
			Type* m_type;
	};
}

#endif

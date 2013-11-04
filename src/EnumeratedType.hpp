#ifndef ENUMERATEDTYPE_HPP
#define ENUMERATEDTYPE_HPP

#include "ASTListTypes.hpp"
#include "Type.hpp"

// Forward Declarations
namespace Meow
{
	class Visitor;
	class TypeVisitor;
	class Identifier;

	class EnumeratedType : public Type
	{
		public:
			EnumeratedType(IdentifierList* entries);

			virtual void accept(Visitor* visitor);
			virtual Type* accept(TypeVisitor* visitor);

		private:
			IdentifierList* m_entries;
	};
}

#endif

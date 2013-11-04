#ifndef RECORDTYPE_HPP
#define RECORDTYPE_HPP

#include "ASTListTypes.hpp"
#include "Type.hpp"

// Forward Declarations
namespace Meow
{
	class Visitor;
	class TypeVisitor;
	class Identifier;

	class RecordType : public Type
	{
		public:
			RecordType(FieldList* fields);

			virtual void accept(Visitor* visitor);
			virtual Type* accept(TypeVisitor* visitor);

		private:
			FieldList* m_fields;
	};
}

#endif

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
			RecordType(FieldList* fields)
				: m_fields(fields)
			{
			}

			virtual void accept(Visitor* visitor) { }
			virtual Type* accept(TypeVisitor* visitor) {return 0;}

		private:
			FieldList* m_fields;
	};
}

#endif

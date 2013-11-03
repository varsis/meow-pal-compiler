#ifndef RECORDFIELD_HPP
#define RECORDFIELD_HPP

#include "Identifier.hpp"
#include "Variable.hpp"
#include "ASTNode.hpp"
#include "LValue.hpp"

namespace Meow
{
	// Forward Declarations
	class Visitor;
	class TypeVisitor;
	class Type;

	class RecordField : public LValue // TODO better names?
	{
		public:
			RecordField(int lineNumber, LValue* record, Identifier* field)
				: m_record(record)
				, m_field(field)
			{
			}

			virtual void accept(Visitor* visitor) { }
			virtual Type* accept(TypeVisitor* visitor) {return 0;}

		private: 
			LValue* m_record;
			Identifier* m_field;
	};
}

#endif

#include "RecordField.hpp"

namespace Meow
{
	RecordField::RecordField(int lineNumber, LValue* record, Identifier* field)
	: m_record(record)
	, m_field(field)
	{
	}
	
	void RecordField::accept(Visitor* visitor)
	{
	}
	
	Type* RecordField::accept(TypeVisitor* visitor)
	{
		return 0;
	}
	
}

#include "RecordType.hpp"

namespace Meow
{
	
	RecordType::RecordType(FieldList* fields)
	: m_fields(fields)
	{
	}
	
	void RecordType::accept(Visitor* visitor)
	{
	}
}


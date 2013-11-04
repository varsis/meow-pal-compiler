#include "RecordField.hpp"
#include "Visitor.hpp"
#include "LValue.hpp"
#include "Identifier.hpp"

namespace Meow
{
	RecordField::RecordField(int lineNumber, LValue* record, Identifier* field)
	: m_record(record)
	, m_field(field)
	{
	}
	
	void RecordField::acceptPreOrder(Visitor* visitor)
	{
		visitor->visit(this);
		m_record->acceptPreOrder(visitor);
		m_field->acceptPreOrder(visitor);
	}

	void RecordField::acceptPostOrder(Visitor* visitor)
	{
		m_record->acceptPostOrder(visitor);
		m_field->acceptPostOrder(visitor);
		visitor->visit(this);
	}
}

#include "RecordType.hpp"
#include "Visitor.hpp"
#include "Field.hpp"

namespace Meow
{
	
	RecordType::RecordType(FieldList* fields)
	: m_fields(fields)
	{
	}
	
	void RecordType::acceptPreOrder(Visitor* visitor)
	{
		visitor->visit(this);

		FieldList::iterator it;
		for (it = m_fields->begin(); it != m_fields->end(); ++it)
		{
			(*it)->acceptPreOrder(visitor);
		}
	}

	void RecordType::acceptPostOrder(Visitor* visitor)
	{
		FieldList::iterator it;
		for (it = m_fields->begin(); it != m_fields->end(); ++it)
		{
			(*it)->acceptPostOrder(visitor);
		}

		visitor->visit(this);
	}
}


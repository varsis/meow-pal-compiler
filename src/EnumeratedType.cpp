#include "EnumeratedType.hpp"
#include "Visitor.hpp"
#include "Identifier.hpp"

namespace Meow
{
	EnumeratedType::EnumeratedType(IdentifierList* entries)
		: m_entries(entries)
	{
	}
	
	void EnumeratedType::acceptPreOrder(Visitor* visitor)
	{
		visitor->visit(this);

		IdentifierList::iterator it;
		for (it = m_entries->begin(); it != m_entries->end(); ++it)
		{
			(*it)->acceptPreOrder(visitor);
		}
	}

	void EnumeratedType::acceptPostOrder(Visitor* visitor)
	{
		IdentifierList::iterator it;
		for (it = m_entries->begin(); it != m_entries->end(); ++it)
		{
			(*it)->acceptPostOrder(visitor);
		}

		visitor->visit(this);
	}
}


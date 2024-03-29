#include "Type.hpp"
#include "Symbol.hpp"

namespace Meow
{
	Type::Type(std::vector<Symbol*>* symbolList)
		: m_typeClass(EnumeratedType)
		, m_symbolList(symbolList)
	{
		// run through list of enum symbols
		for (unsigned int i = 0; i < symbolList->size(); ++i)
		{
			// assign type to this new enum type
			symbolList->at(i)->setType(this);

			// assign integer values for ordering
			symbolList->at(i)->setConstantValue((int)i);
		}

		m_minValue.int_val  = 0;
		m_maxValue.int_val = symbolList->size() - 1;
		m_typeSize = 1;
	}
}

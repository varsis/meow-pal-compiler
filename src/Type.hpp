#ifndef TYPE_HPP
#define TYPE_HPP

#include <vector>

namespace Meow
{
	class Symbol;

	class Type
	{
		enum TypeClass
		{
			EnumeratedType,
			ArrayType,
			RecordType,
			SimpleType,
		};

		public:

			Type() : m_typeClass(SimpleType)
			{
			}
			
			Type(std::vector<Symbol*>* symbolList)
				: m_typeClass(EnumeratedType)
				, m_symbolList(symbolList)
			{
			}

			TypeClass getTypeClass()
			{
				return m_typeClass;
			}

			std::vector<Symbol*>* getEnumSymbols()
			{
				return m_symbolList;
			}


		private:

			TypeClass m_typeClass;

			std::vector<Symbol*>* m_symbolList;

	};
}

#endif

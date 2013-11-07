#ifndef TYPE_HPP
#define TYPE_HPP

#include <vector>

namespace Meow
{
	class Symbol;

	class Type
	{
		public:

			enum TypeClass
			{
				EnumeratedType,
				ArrayType,
				RecordType,
				SimpleType,
			};


			typedef std::pair<std::string*, Meow::Type*> IdTypePair;
			typedef std::vector<IdTypePair*> IdTypePairList;

			Type() : m_typeClass(SimpleType)
			{
			}
			
			Type(std::vector<Symbol*>* symbolList)
				: m_typeClass(EnumeratedType)
				, m_symbolList(symbolList)
			{
			}

			Type(void* index_type, Type* elementType)
				: m_typeClass(ArrayType)
				, m_elementType(elementType)
			{
			}

			Type(IdTypePairList* fields)
				: m_typeClass(ArrayType)
				, m_fields(fields)
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

			Type* getElementType()
			{
				return m_elementType;
			}

			IdTypePairList* getFields()
			{
				return m_fields;
			}

		private:

			TypeClass m_typeClass;

			Type* m_elementType;
			std::vector<Symbol*>* m_symbolList;
			IdTypePairList* m_fields;

	};
}

#endif

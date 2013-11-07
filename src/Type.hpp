#ifndef TYPE_HPP
#define TYPE_HPP

#include <vector>
#include "Symbol.hpp"
#include "AuxiliaryTypes.hpp"

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
			
			Type(std::vector<Symbol*>* symbolList);

			Type(Type* elementType, Type* indexType)
				: m_typeClass(ArrayType)
				  , m_elementType(elementType)
				  , m_indexType(indexType)
			{
				// TODO m_indexRange is first element in ordinal index type to last
				// element (eg false .. true, 'a' .. 'z', MININT .. MAXINT)
			}

			Type(Type* elementType, Type* indexType, ArrayIndexRange indexRange)
				: m_typeClass(ArrayType)
				, m_elementType(elementType)
				, m_indexRange(indexRange)
				, m_indexType(indexType)
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
			
			// simple + enum...
			Value getMaxValue() { return m_maxValue; }
			Value getMinValue() { return m_minValue; }

			// enum
			std::vector<Symbol*>* getEnumSymbols()
			{
				return m_symbolList;
			}

			// array
			Type* getElementType()
			{
				return m_elementType;
			}

			Type* getIndexType()
			{
				return m_indexType;
			}

			ArrayIndexRange getIndexRange()
			{
				return m_indexRange;
			}

			// record
			IdTypePairList* getFields()
			{
				return m_fields;
			}

		private:

			TypeClass m_typeClass;

			// simple + enum
			Value m_maxValue;
			Value m_minValue;

			// arrays
			Type* m_elementType;
			ArrayIndexRange m_indexRange;
			Type* m_indexType;

			// enums
			std::vector<Symbol*>* m_symbolList;

			// records
			IdTypePairList* m_fields;

	};
}

#endif

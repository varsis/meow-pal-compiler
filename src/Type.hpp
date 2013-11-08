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
				SimpleType,
				EnumeratedType,
				ArrayType,
				RecordType,
				StringLiteralType,
			};

			typedef std::pair<std::string*, Meow::Type*> IdTypePair;
			typedef std::vector<IdTypePair*> IdTypePairList;

			// Simple type
			Type() : m_typeClass(SimpleType)
			{
			}
			
			// Enum
			Type(std::vector<Symbol*>* symbolList);

			// Array
			Type(Type* elementType, Type* indexType)
				: m_typeClass(ArrayType)
				  , m_elementType(elementType)
				  , m_indexType(indexType)
			{
			}

			// Array
			Type(Type* elementType, Type* indexType, ArrayIndexRange indexRange)
				: m_typeClass(ArrayType)
				, m_elementType(elementType)
				, m_indexRange(indexRange)
				, m_indexType(indexType)
			{
			}

			// Record
			Type(IdTypePairList* fields)
				: m_typeClass(RecordType)
				, m_fields(fields)
			{
			}

			// String Literal
			Type(std::string literal)
				: m_typeClass(StringLiteralType)
				, m_stringLiteral(literal)
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

			// string literal
			std::string getStringLiteral() { return m_stringLiteral; }

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

			// string literal
			std::string m_stringLiteral;

	};
}

#endif

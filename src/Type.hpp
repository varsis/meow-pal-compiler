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
				, m_typeSize(1)
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
				m_indexRange.start = 0;
				m_indexRange.end = 0;
				if (indexType)
				{
					m_typeSize = indexType->getEnumSymbols()->size();
				}
				else 
				{
					m_typeSize = 1;
				}
			}

			// Array
			Type(Type* elementType, Type* indexType, ArrayIndexRange indexRange)
				: m_typeClass(ArrayType)
				, m_elementType(elementType)
				, m_indexRange(indexRange)
				, m_indexType(indexType)
			{
				if (elementType)
				{
					m_typeSize = (indexRange.end - indexRange.start + 1) * elementType->getTypeSize();
				}
				else
				{
					m_typeSize = 1;
				}
			}

			// Record
			Type(IdTypePairList* fields)
				: m_typeClass(RecordType)
				, m_fields(fields)
			{
				if (fields)
				{
					m_typeSize = 0;
					for(int i=0; i<(int)fields->size(); i++)
					{
						m_typeSize += fields->at(i)->second->getTypeSize();
					}
				}
				else
				{
					m_typeSize = 1;
				}
			}

			// String Literal
			Type(std::string literal)
				: m_typeClass(StringLiteralType)
				, m_stringLiteral(literal)
			{
				m_typeSize = m_stringLiteral.size() + 1; // size of null terminated string
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

			int getTypeSize()
			{
				return m_typeSize;
			}

			// string literal
			std::string getStringLiteral() { return m_stringLiteral; }

		private:

			TypeClass m_typeClass;
			int m_typeSize;

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

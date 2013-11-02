#ifndef RECORDFIELD_HPP
#define RECORDFIELD_HPP

#include "Identifier.hpp"
#include "Variable.hpp"
#include "ASTNode.hpp"
#include "LValue.hpp"

namespace Meow
{
	// Forward Declarations
	class Visitor;
	class TypeVisitor;
	class Type;

	class RecordField : public LValue
	{
		public:
			RecordField(int lineNumber, Variable* record, Identifier* field);

			virtual void accept(Visitor visitor) = 0;
			virtual Type accept(TypeVisitor visitor) = 0;

	};
}

#endif

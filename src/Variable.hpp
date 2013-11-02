#ifndef VARIABLE_HPP
#define VARIABLE_HPP

#include "Identifier.hpp"
#include "ASTNode.hpp"
#include "LValue.hpp"

namespace Meow
{
	// Forward Declarations
	class Visitor;
	class TypeVisitor;
	class Type;

	class Variable : public LValue
	{
		public:
			Variable(int lineNumber, Identifier* id);

			virtual void accept(Visitor visitor) = 0;
			virtual Type accept(TypeVisitor visitor) = 0;

	};
}

#endif

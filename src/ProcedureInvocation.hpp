#ifndef PROCINVOKE_HPP
#define PROCINVOKE_HPP

#include "Statement.hpp"
#include "Identifier.hpp"
#include "ASTNode.hpp"

namespace Meow
{
	// Forward Declarations
	class Visitor;
	class TypeVisitor;
	class Arguments;
	class Type;

	class ProcedureInvocation : public Statement
	{
		public:
			ProcedureInvocation(Identifier* procId, Arguments* a);

			virtual void accept(Visitor visitor) = 0;
			virtual Type accept(TypeVisitor visitor) = 0;

	};
}

#endif

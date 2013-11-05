#ifndef PROCINVOKE_HPP
#define PROCINVOKE_HPP

#include "Statement.hpp"
#include "Identifier.hpp"
#include "ASTNode.hpp"

namespace Meow
{
	// Forward Declarations
	class Visitor;
	class Arguments;
	class Type;

	class ProcedureInvocation : public Statement
	{
		public:
			ProcedureInvocation(Identifier* procId, Arguments* a);

			virtual void acceptPreOrder(Visitor* visitor);
			virtual void acceptPostOrder(Visitor* visitor);

		private: 
			Identifier* m_procedureId;
			Arguments* m_arguments;
	};
}

#endif

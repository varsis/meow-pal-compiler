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
			ProcedureInvocation(Identifier* procId, Arguments* a)
				: m_procedureId(procId)
				, m_arguments(a)
			{
			}

			virtual void accept(Visitor* visitor) { }
			virtual Type* accept(TypeVisitor* visitor) {return 0;}

		private: 
			Identifier* m_procedureId;
			Arguments* m_arguments;
	};
}

#endif

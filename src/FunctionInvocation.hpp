#ifndef FUNCINVOKE_HPP
#define FUNCINVOKE_HPP

#include "Expression.hpp"
#include "Identifier.hpp"
#include "ASTNode.hpp"

namespace Meow
{
	// Forward Declarations
	class Visitor;
	class TypeVisitor;
	class Arguments;
	class Type;

	class FunctionInvocation : public Expression
	{
		public:
			FunctionInvocation(Identifier* name, Arguments* a)
				: m_functionId(name)
				, m_arguments(a)
			{
			}

			virtual void accept(Visitor* visitor) { }
			virtual Type* accept(TypeVisitor* visitor) {return 0;}

		private: 
			Identifier* m_functionId;
			Arguments* m_arguments;
	};
}

#endif

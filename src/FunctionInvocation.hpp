#ifndef FUNCINVOKE_HPP
#define FUNCINVOKE_HPP

#include "Expression.hpp"
#include "Identifier.hpp"
#include "ASTNode.hpp"

namespace Meow
{
	// Forward Declarations
	class Visitor;
	class Arguments;
	class Type;

	class FunctionInvocation : public Expression
	{
		public:
			FunctionInvocation(Identifier* name, Arguments* a);

			virtual void acceptPreOrder(Visitor* visitor);
			virtual void acceptPostOrder(Visitor* visitor);

		private: 
			Identifier* m_functionId;
			Arguments* m_arguments;
	};
}

#endif

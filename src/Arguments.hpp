#ifndef ARGUMENTS_HPP
#define ARGUMENTS_HPP

#include "Expression.hpp"
#include "ASTNode.hpp"

namespace Meow
{
	// Forward Declarations
	class Visitor;
	class TypeVisitor;
	class Type;

	class Arguments : public ASTNode
	{
		public:
			Arguments();

			void addArgument(Expression* e);

			virtual void accept(Visitor visitor) = 0;
			virtual Type accept(TypeVisitor visitor) = 0;

	};
}

#endif

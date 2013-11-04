#ifndef ARGUMENTS_HPP
#define ARGUMENTS_HPP

#include "Expression.hpp"
#include "ASTNode.hpp"
#include "ASTListTypes.hpp"

namespace Meow
{
	// Forward Declarations
	class Visitor;
	class Type;

	class Arguments : public ASTNode
	{
		public:
			Arguments();

			void addArgument(Expression* e);

			virtual void accept(Visitor* visitor);

		private: 
			ExpressionList m_arguments;

	};
}

#endif

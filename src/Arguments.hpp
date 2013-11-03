#ifndef ARGUMENTS_HPP
#define ARGUMENTS_HPP

#include "Expression.hpp"
#include "ASTNode.hpp"
#include "ASTListTypes.hpp"

namespace Meow
{
	// Forward Declarations
	class Visitor;
	class TypeVisitor;
	class Type;

	class Arguments : public ASTNode
	{
		public:
			Arguments() {}

			void addArgument(Expression* e)
			{
				m_arguments.push_back(e);
			}

			virtual void accept(Visitor* visitor) { }
			virtual Type* accept(TypeVisitor* visitor) {return 0;}

		private: 
			ExpressionList m_arguments;

	};
}

#endif

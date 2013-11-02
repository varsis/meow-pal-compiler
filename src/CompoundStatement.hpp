#ifndef COMPOUNDSTATEMENT_HPP
#define COMPOUNDSTATEMENT_HPP

#include "Statement.hpp"
#include "ASTNode.hpp"

namespace Meow
{
	// Forward Declarations
	class Visitor;
	class TypeVisitor;
	class Type;

	class CompoundStatement : public Statement
	{
		public:
			virtual void accept(Visitor visitor) = 0;
			virtual Type accept(TypeVisitor visitor) = 0;

			virtual void addStatement(Statement* statement);
	};
}

#endif

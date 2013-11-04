#ifndef COMPOUNDSTATEMENT_HPP
#define COMPOUNDSTATEMENT_HPP

#include "Statement.hpp"
#include "ASTListTypes.hpp"

namespace Meow
{
	// Forward Declarations
	class Visitor;
	class TypeVisitor;
	class Type;

	class CompoundStatement : public Statement
	{
		public:
			virtual void accept(Visitor* visitor);
			virtual Type* accept(TypeVisitor* visitor);

			unsigned int statementCount() const;

			Statement* getStatement(int index) const;

			virtual void addStatement(Statement* statement);
		private:
			StatementList m_statements;
		

	};
}
#endif

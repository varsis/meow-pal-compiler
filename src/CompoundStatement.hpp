#ifndef COMPOUNDSTATEMENT_HPP
#define COMPOUNDSTATEMENT_HPP

#include "Statement.hpp"
#include "ASTListTypes.hpp"

namespace Meow
{
	// Forward Declarations
	class Visitor;
	class Type;

	class CompoundStatement : public Statement
	{
		public:
			virtual void acceptPreOrder(Visitor* visitor);
			virtual void acceptPostOrder(Visitor* visitor);

			unsigned int statementCount() const;

			Statement* getStatement(int index) const;

			virtual void addStatement(Statement* statement);
		private:
			StatementList m_statements;
		

	};
}
#endif

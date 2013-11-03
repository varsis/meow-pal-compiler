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
			virtual void accept(Visitor* visitor) { }
			virtual Type* accept(TypeVisitor* visitor) {return 0;}

			unsigned int statementCount() const
			{
				return m_statements.size();
			}

			Statement* getStatement(int index) const
			{
				return m_statements[index];
			}

			virtual void addStatement(Statement* statement)
			{
				m_statements.push_back(statement);
			}

		private:
			StatementList m_statements;
			
	};
}

#endif

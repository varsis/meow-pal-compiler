#include "CompoundStatement.hpp"
#include "Visitor.hpp"
#include "Statement.hpp"

namespace Meow
{
	void CompoundStatement::acceptPreOrder(Visitor* visitor)
	{
		visitor->visit(this);

		StatementList::iterator it;
		for (it = m_statements.begin(); it != m_statements.end(); ++it)
		{
			(*it)->acceptPreOrder(visitor);
		}
	}

	void CompoundStatement::acceptPostOrder(Visitor* visitor)
	{
		StatementList::iterator it;
		for (it = m_statements.begin(); it != m_statements.end(); ++it)
		{
			(*it)->acceptPostOrder(visitor);
		}

		visitor->visit(this);
	}

	unsigned int CompoundStatement::statementCount() const
	{
		return m_statements.size();
	}
	
	Statement* CompoundStatement::getStatement(int index) const
	{
		return m_statements[index];
	}
	
	void CompoundStatement::addStatement(Statement* statement)
	{
		m_statements.push_back(statement);
	}
	
}



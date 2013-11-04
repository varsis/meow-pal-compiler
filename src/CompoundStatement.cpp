#include "CompoundStatement.hpp"

namespace Meow
{
	void CompoundStatement::accept(Visitor* visitor)
	{
	}
	
	Type* CompoundStatement::accept(TypeVisitor* visitor)
	{
		return 0;
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



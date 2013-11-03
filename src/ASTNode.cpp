#include "ASTNode.hpp"

namespace Meow
{
	ASTNode::ASTNode()
	{
	}

	unsigned int ASTNode::getLineNumber() const
	{
		return m_lineNumber;
	}

	void ASTNode::setLineNumber(unsigned int number)
	{
		 m_lineNumber = number;
	}
}

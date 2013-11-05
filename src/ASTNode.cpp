#include "ASTNode.hpp"
#include "Visitor.hpp"

namespace Meow
{
	ASTNode::ASTNode()
	{
	}

	void ASTNode::acceptPreOrder(Visitor* visitor)
	{
		visitor->pushNode(this);
		acceptPreOrderInternal(visitor);
		visitor->popNode(this);
	}

	void ASTNode::acceptPostOrder(Visitor* visitor)
	{
		visitor->pushNode(this);
		acceptPostOrderInternal(visitor);
		visitor->pushNode(this);
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

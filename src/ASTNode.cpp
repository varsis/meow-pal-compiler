#include "ASTNode.hpp"
#include "Visitor.hpp"

namespace Meow
{
	ASTNode::ASTNode()
	{
	}

	void ASTNode::acceptPreOrder(Visitor* visitor)
	{
		visitor->increaseLevel();
		acceptPreOrderInternal(visitor);
		visitor->decreaseLevel();
	}

	void ASTNode::acceptPostOrder(Visitor* visitor)
	{
		visitor->increaseLevel();
		acceptPostOrderInternal(visitor);
		visitor->decreaseLevel();
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

#include "Visitor.hpp"

namespace Meow
{
	void Visitor::pushNode(const ASTNode* node)
	{
		m_treeLevel++;
	}

	void Visitor::popNode(const ASTNode* node)
	{
		m_treeLevel++;
	}
}

#ifndef ASTNODE_HPP
#define ASTNODE_HPP

namespace Meow
{
	class ASTNode
	{
		public:
			ASTNode();
			unsigned int getLineNumber() const;
			void setLineNumber(unsigned int lineNumber);
		private:
			unsigned int m_lineNumber;
	};
}

#endif

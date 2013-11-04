#ifndef ASTNODE_HPP
#define ASTNODE_HPP

namespace Meow
{
	class Visitor;

	class ASTNode
	{
		public:
			ASTNode();
			unsigned int getLineNumber() const;
			void setLineNumber(unsigned int lineNumber);

			virtual void acceptPreOrder(Visitor* visitor) = 0;
			virtual void acceptPostOrder(Visitor* visitor) = 0;

		private:
			unsigned int m_lineNumber;
	};
}

#endif

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

			virtual void acceptPreOrder(Visitor* visitor);
			virtual void acceptPostOrder(Visitor* visitor);

			// TODO
			// Make these abstract here,
			// rename acceptPreOrder and acceptPostOrder functions to 
			// acceptPreOrderInternal, acceptPostOrderInternal in all subclasses
			// (but don't change any calls to acceptPreOrder(visitor), acceptPostOrder(visitor))
			// -> rationale: this is so we can keep track of the tree level as we traverse it
			virtual void acceptPreOrderInternal(Visitor* visitor) { }
			virtual void acceptPostOrderInternal(Visitor* visitor) { }

		private:
			unsigned int m_lineNumber;
	};
}

#endif

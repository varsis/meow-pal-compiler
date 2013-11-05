#ifndef PARAMETER_HPP
#define PARAMETER_HPP

#include "ASTNode.hpp"

namespace Meow
{
	class Identifier;
	class Visitor;
	class Type;

	class Parameter : public ASTNode
	{
		public:
			Parameter(int lineNumber, Identifier* name, Identifier* type, bool varParam);

			Identifier* getName();
			Identifier* getType();

			virtual void acceptPreOrder(Visitor* visitor);
			virtual void acceptPostOrder(Visitor* visitor);
		
		private:
			Identifier* m_name;
			Identifier* m_type;
			bool m_varParam;
	};
}

#endif

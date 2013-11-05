#ifndef VARIABLE_HPP
#define VARIABLE_HPP

#include "Identifier.hpp"
#include "ASTNode.hpp"
#include "LValue.hpp"

namespace Meow
{
	class Visitor;
	class Identifier;
	class Type;

	class Variable : public LValue
	{
		public:
			Variable(int lineNumber, Identifier* id);

			virtual void acceptPreOrder(Visitor* visitor);
			virtual void acceptPostOrder(Visitor* visitor);

		private: 
			Identifier* m_identifier;

	};
}

#endif

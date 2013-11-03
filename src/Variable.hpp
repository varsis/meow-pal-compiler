#ifndef VARIABLE_HPP
#define VARIABLE_HPP

#include "Identifier.hpp"
#include "ASTNode.hpp"
#include "LValue.hpp"

namespace Meow
{
	// Forward Declarations
	class Visitor;
	class TypeVisitor;
	class Identifier;
	class Type;

	class Variable : public LValue
	{
		public:
			Variable(int lineNumber, Identifier* id)
				: m_identifier(id)
			{
			}


			virtual void accept(Visitor* visitor) { }
			virtual Type* accept(TypeVisitor* visitor) {return 0;}

		private: 
			Identifier* m_identifier;

	};
}

#endif

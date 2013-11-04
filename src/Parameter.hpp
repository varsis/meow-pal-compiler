#ifndef PARAMETER_HPP
#define PARAMETER_HPP

#include "ASTNode.hpp"

namespace Meow
{
	class Identifier;
	class Visitor;
	class Type;
	class TypeVisitor;

	class Parameter : public ASTNode
	{
		public:
			Parameter(int lineNumber, Identifier* name, Identifier* type, bool varParam);

			Identifier* getName();
			Identifier* getType();

			void accept(Visitor* visitor);
			const Type* accept(TypeVisitor* typeVisitor);
		
		private:
			Identifier* m_name;
			Identifier* m_type;
			bool m_varParam;
	};
}

#endif

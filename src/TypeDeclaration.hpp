#ifndef TYPEDECLARATION_HPP
#define TYPEDECLARATION_HPP

#include <string>
#include "ASTNode.hpp"

namespace Meow
{
	class Identifier;
	class Visitor;
	class Type;

	class TypeDeclaration : public ASTNode
	{
		public:
			TypeDeclaration(int lineNumber, Identifier* identifier, Type* type);

			virtual void acceptPreOrder(Visitor* visitor);
			virtual void acceptPostOrder(Visitor* visitor);

			const Identifier* getIdentifier() const;

			const Type* getType() const;
		
		private:
			Identifier* m_identifier;
			Type* m_type;
	};
}

#endif

#ifndef TYPEDECLARATION_HPP
#define TYPEDECLARATION_HPP

#include <string>
#include "ASTNode.hpp"

namespace Meow
{
	class Identifier;
	class Visitor;
	class Type;
	class TypeVisitor;

	class TypeDeclaration : public ASTNode
	{
		public:
			TypeDeclaration(int lineNumber, Identifier* identifier, Type* type)
				: m_identifier(identifier)
				, m_type(type)
			{
			}
		
			void accept(Visitor* visitor);
			const Type* accept(TypeVisitor* typeVisitor);

			const Identifier* getIdentifier() const
			{	
				return m_identifier;
			}

			const Type* getType() const;
		
		private:
			Identifier* m_identifier;
			Type* m_type;
	};
}

#endif

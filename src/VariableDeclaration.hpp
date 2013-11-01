#ifndef VARIABLEDECLARATION_HPP
#define VARIABLEDECLARATION_HPP

#include <string>
#include "ASTNode.hpp"

namespace Meow
{
	class Type;
	class Visitor;
	class TypeVisitor;
	class Identifier;

	class VariableDeclaration : public ASTNode
	{
		public:
			VariableDeclaration(int lineNumber, Identifier* identifer, Type* type);
			~VariableDeclaration();
		
			void accept(Visitor visitor);
			const Type* accept(TypeVisitor typeVisitor);

			const Identifier* get_identifier() const;
			const Type* get_type() const;
		
		private:
			Identifier* identifier;
			Type* type;
	};
}

#endif

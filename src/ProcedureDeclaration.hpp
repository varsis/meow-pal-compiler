#ifndef PROCEDUREDECLARATION_HPP
#define PROCEDUREDECLARATION_HPP

#include "ASTNode.hpp"

namespace Meow
{
	class Identifier;
	class Visitor;
	class Type;
	class TypeVisitor;

	// TODO -- how to differentiate between procedures and functions?

	class ProcedureDeclaration : public ASTNode
	{
		public:
			ProcedureDeclaration(int lineNumber, Identifier* identifer, Type* type);
		
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

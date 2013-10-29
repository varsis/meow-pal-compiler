#ifndef VISITOR_HPP
#define VISITOR_HPP

namespace Meow
{
	class Visitor {
		public:
			virtual void visit(const Program* prog) = 0;
			virtual void visit(const ConstantDeclaration* constantDecl) = 0;
			virtual void visit(const Identifier* identifier) = 0;
			virtual void visit(const IdentifierType* identifierType) = 0;
			virtual void visit(const TypeDeclaration* typeDecl) = 0;
			virtual void visit(const VariableDeclaration* varDecl) = 0;

			// Add more as we add more node types
	};
}

#endif

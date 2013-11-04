#ifndef PROCEDUREDECLARATION_HPP
#define PROCEDUREDECLARATION_HPP

#include "ASTNode.hpp"

namespace Meow
{
	class Identifier;
	class Visitor;
	class Type;
	class TypeVisitor;
	class Declarations;
	class CompoundStatement;
	class ProcedureHeading;

	class ProcedureDeclaration : public ASTNode
	{
		public:
			ProcedureDeclaration(int lineNumber,
					     ProcedureHeading* heading,
					     Declarations* procedureDeclarations,
					     CompoundStatement* statements);
		
			void accept(Visitor* visitor);
			const Type* accept(TypeVisitor* typeVisitor);

			const ProcedureHeading* getHeading() const;

			const Declarations* getDeclarations() const;
		
		private:
			ProcedureHeading* m_heading;
			Declarations* m_declarations;
			CompoundStatement* m_statements;
	};
}

#endif

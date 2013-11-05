#ifndef PROCEDUREDECLARATION_HPP
#define PROCEDUREDECLARATION_HPP

#include "ASTNode.hpp"

namespace Meow
{
	class Identifier;
	class Visitor;
	class Type;
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
		
			virtual void acceptPreOrder(Visitor* visitor);
			virtual void acceptPostOrder(Visitor* visitor);

			const ProcedureHeading* getHeading() const;

			const Declarations* getDeclarations() const;
		
		private:
			ProcedureHeading* m_heading;
			Declarations* m_declarations;
			CompoundStatement* m_statements;
	};
}

#endif

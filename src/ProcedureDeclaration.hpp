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
						CompoundStatement* statements)
				: m_heading(heading)
				, m_declarations(procedureDeclarations)
				, m_statements(statements)
			{
			}
		
			void accept(Visitor* visitor);
			const Type* accept(TypeVisitor* typeVisitor);

			const ProcedureHeading* getHeading() const
			{	
				return m_heading;
			}

			const Declarations* getDeclarations() const
			{	
				return m_declarations;
			}
		
		private:
			ProcedureHeading* m_heading;
			Declarations* m_declarations;
			CompoundStatement* m_statements;
	};
}

#endif

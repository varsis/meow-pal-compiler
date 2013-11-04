#ifndef PROGRAM_HPP
#define PROGRAM_HPP

#include "ASTNode.hpp"
#include "ASTListTypes.hpp"
#include "Visitor.hpp"

namespace Meow
{
	class Type; 
	class Declarations;
	class CompoundStatement;

	class Program : ASTNode
	{
		public:
			Program(Declarations* declarations, CompoundStatement* statements);

			~Program();
			
			void accept(Visitor* visitor);
			
			/*
			const ConstantDeclarationList getConstantDeclarationList() const;
			const TypeDeclarationList getTypeDeclarationList() const;
			const ProcedureDeclarationList getProcedureDeclarationList() const;
			*/
			const CompoundStatement* getStatements() const;
			const Declarations* getDeclarations() const;
		
		private:
			/*
			ConstantDeclarationList constantDeclarationList;
			TypeDeclarationList typeDeclarationList;
			ProcedureDeclarationList procedureDeclarationList;
			*/
			Declarations* m_declarations;
			CompoundStatement* m_statements;
	};
}
#endif

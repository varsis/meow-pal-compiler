#ifndef PROGRAM_HPP
#define PROGRAM_HPP

#include "ASTListTypes.hpp"
#include "Visitor.hpp"
#include "CheckTypeVisitor.hpp"

namespace Meow
{
	class Type; 
	class TypeVisitor; 

	class Program
	{
		public:
			Program(ConstantDeclarationList constDeclList,
				TypeDeclarationList typeDeclList,
				ProcedureDeclarationList
				procedureDeclList);
			~Program();
			
			void accept(Visitor visitor);
			Type* accept(TypeVisitor typeVisitor);
			
			const ConstantDeclarationList getConstantDeclarationList() const;
			const TypeDeclarationList getTypeDeclarationList() const;
			const ProcedureDeclarationList getProcedureDeclarationList() const;
			const StatementList getStatementList() const;
		
		private:
			ConstantDeclarationList constantDeclarationList;
			TypeDeclarationList typeDeclarationList;
			ProcedureDeclarationList procedureDeclarationList;
			StatementList statementList;
	};
}
#endif

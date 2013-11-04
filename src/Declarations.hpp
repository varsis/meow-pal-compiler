#ifndef DECLARATIONS_HPP
#define DECLARATIONS_HPP

#include "ASTNode.hpp"
#include "ASTListTypes.hpp"
#include "Visitor.hpp"

namespace Meow
{
	class Type; 

	class Declarations : ASTNode
	{
		public:
			Declarations(ConstantDeclarationList* constDeclList,
				TypeDeclarationList* typeDeclList,
				VariableDeclarationList* variableDeclList,
				ProcedureDeclarationList* procedureDeclList);

			~Declarations();
			
			void accept(Visitor* visitor);
			
			const ConstantDeclarationList* getConstantDeclarationList() const;

			const TypeDeclarationList* getTypeDeclarationList() const;

			const VariableDeclarationList* getVariableDeclarationList() const;

			const ProcedureDeclarationList* getProcedureDeclarationList() const;
		
		private:
			ConstantDeclarationList* m_constantDeclarationList;
			TypeDeclarationList* m_typeDeclarationList;
			VariableDeclarationList* m_variableDeclarationList;
			ProcedureDeclarationList* m_procedureDeclarationList;
	};
}
#endif

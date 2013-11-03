#include "Declarations.hpp"
namespace Meow
{
	Declarations::Declarations(ConstantDeclarationList* constDeclList,
				TypeDeclarationList* typeDeclList,
				VariableDeclarationList* variableDeclList,
				ProcedureDeclarationList* procedureDeclList)
		: m_constantDeclarationList(constDeclList)
		, m_typeDeclarationList(typeDeclList)
		, m_variableDeclarationList(variableDeclList)
		, m_procedureDeclarationList(procedureDeclList)
	{
	}
}

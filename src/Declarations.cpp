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
	
	void Declarations::accept(Visitor* visitor)
	{
	}
	
	const ConstantDeclarationList* Declarations::getConstantDeclarationList() const
	{
		return m_constantDeclarationList;
	}
	
	const TypeDeclarationList* Declarations::getTypeDeclarationList() const
	{
		return m_typeDeclarationList;
	}
	
	const VariableDeclarationList* Declarations::getVariableDeclarationList() const
	{
		return m_variableDeclarationList;
	}
	
	const ProcedureDeclarationList* Declarations::getProcedureDeclarationList() const
	{
		return m_procedureDeclarationList;
	}
}

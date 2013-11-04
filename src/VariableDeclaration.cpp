#include "VariableDeclaration.hpp"
namespace Meow
{
	VariableDeclaration::VariableDeclaration(int lineNumber, Type* type)
	: m_type(type)
	{
	}
	
	VariableDeclaration::~VariableDeclaration()
	{
		
	}
	
	void VariableDeclaration::accept(Visitor* visitor)
	{
	}
	
	void VariableDeclaration::addIdentifier(Identifier* id)
	{
		m_identifiers.push_back(id);
	}
	
	const vector<Identifier*>* VariableDeclaration::getIdentifiers() const
	{
		return &m_identifiers;
	}
	
	const Type* VariableDeclaration::getType() const
	{
		return m_type;
	}
}


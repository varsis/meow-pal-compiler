#include "ConstantDeclaration.hpp"
#include "Identifier.hpp"

namespace Meow
{
	ConstantDeclaration::ConstantDeclaration(int lineNumber,
						Identifier* identifier,
						Expression* expression)
		: m_identifier(identifier)
	{
	}
	
	void ConstantDeclaration::accept(Visitor* visitor)
	{
	}
	const Type* ConstantDeclaration::accept(TypeVisitor* typeVisitor)
	{
		
	}
	
	const Type* ConstantDeclaration::getType() const
	{
	}
	
	const Identifier* ConstantDeclaration::getIdentifier() const
	{
		return m_identifier;
	}
	
	const Expression* ConstantDeclaration::getExtpression() const
	{
	}
}


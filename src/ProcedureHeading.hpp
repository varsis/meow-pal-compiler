#ifndef PROCEDUREHEADING_HPP
#define PROCEDUREHEADING_HPP

#include "ASTNode.hpp"

namespace Meow
{
	class Identifier;
	class Visitor;
	class Type;
	class TypeVisitor;
	class ParameterList;

	class ProcedureHeading : public ASTNode
	{
		public:
			ProcedureHeading(int lineNumber,
								Identifier* identifier,
								ParameterList* params,
								Type* type)
				: m_identifier(identifier)
				, m_parameters(params)
				, m_type(type)
			{
			}
		
			void accept(Visitor* visitor);
			const Type* accept(TypeVisitor* typeVisitor);

			const Identifier* getIdentifier() const
			{	
				return m_identifier;
			}

			const Type* getType() const;
		
		private:
			Identifier* m_identifier;
			ParameterList* m_parameters;
			Type* m_type;
	};
}

#endif

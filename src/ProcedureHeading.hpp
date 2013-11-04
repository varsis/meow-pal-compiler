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
					 Identifier* type);
		
			void accept(Visitor* visitor);
			const Type* accept(TypeVisitor* typeVisitor);

			const Identifier* getIdentifier() const;

			const ParameterList* getParameters() const;

			const Identifier* getType() const;
		
		private:
			Identifier* m_identifier;
			ParameterList* m_parameters;
			Identifier* m_type;
	};
}

#endif

#ifndef CONSTANTDECLARATION_HPP
#define CONSTANTDECLARATION_HPP

#include <string>
#include "ASTNode.hpp"
#include "RealConstant.hpp"

namespace Meow
{

	class Type;
	class Expression;
	class Identifier;
	class Visitor;

	class ConstantDeclaration : public ASTNode
	{
		public:
			ConstantDeclaration(int lineNumber,
						Identifier* identifer,
						Expression* expression);

			void accept(Visitor* visitor);

			const Type* getType() const;
			const Identifier* getIdentifier() const;
			const Expression* getExpression() const;
		
		private:
			Type* m_type; // ???
			Identifier* m_identifier;
			Expression* m_expression;
	};
}

#endif

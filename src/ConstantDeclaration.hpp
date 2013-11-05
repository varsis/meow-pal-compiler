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

			virtual void acceptPreOrder(Visitor* visitor);
			virtual void acceptPostOrder(Visitor* visitor);

			const Identifier* getIdentifier() const;
			const Expression* getExpression() const;
		
		private:
			Identifier* m_identifier;
			Expression* m_expression;
	};
}

#endif

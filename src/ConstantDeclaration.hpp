#ifndef CONSTANTDECLARATION_HPP
#define CONSTANTDECLARATION_HPP

class Type;
class Expression;
class Identifier;

#include <string>
#include "LineNumberInformation.hpp"

namespace Meow
{
	class ConstantDeclaration : public LineNumberInformation {
		public:
			ConstantDeclaration(int lineNumber, Type* type, Identifier* identifer, Expression* expression);
		
			void accept(Visitor visitor);
			const Type* accept(TypeVisitor typeVisitor);

			const Type* get_type() const;
			const Identifier* get_identifier() const;
			const Expression* get_expression() const;
		
		private:
			Type* type;
			Identifier* identifier;
			Expression* expression;
	};
}

#endif
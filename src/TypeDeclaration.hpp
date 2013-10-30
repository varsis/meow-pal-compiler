#ifndef TYPEDECLARATION_HPP
#define TYPEDECLARATION_HPP

#include <string>
#include "LineNumberInformation.hpp"

namespace Meow
{
	class TypeDeclaration : public LineNumberInformation {
		public:
			TypeDeclaration(int lineNumber, Identifier* identifer, Type* type);
		
			void accept(Visitor visitor);
			const Type* accept(TypeVisitor typeVisitor);

			const Identifier* get_identifier() const;
			const Type* get_type() const;
		
		private:
			Identifier* identifier;
			Type* type;
	};
}

#endif
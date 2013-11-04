#ifndef IDENTIFIER_HPP
#define IDENTIFIER_HPP

#include <string>
#include "ASTNode.hpp"

namespace Meow
{
	class Visitor;
	class TypeVisitor;
	class Type;

	class Identifier : public ASTNode
	{
		public:
			Identifier(int lineNumber, const char* identifierName);
		
			void accept(Visitor* visitor);
			Type* accept(TypeVisitor* typeVisitor);
			
			inline std::string toString() const;
		
		private:
			std::string m_name;
	};
}

#endif

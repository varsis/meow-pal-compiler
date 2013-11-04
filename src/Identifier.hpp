#ifndef IDENTIFIER_HPP
#define IDENTIFIER_HPP

#include <string>
#include "ASTNode.hpp"

namespace Meow
{
	class Visitor;
	class Type;

	class Identifier : public ASTNode
	{
		public:
			Identifier(int lineNumber, const char* identifierName);
		
			void accept(Visitor* visitor);
			
			std::string toString() const;
		
		private:
			std::string m_name;
	};
}

#endif

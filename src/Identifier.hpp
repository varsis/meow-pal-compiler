#ifndef IDENTIFIER_HPP
#define IDENTIFIER_HPP

#include <string>
#include "LineNumberInformation.hpp"

namespace Meow
{
	class Identifier : public LineNumberInformation {
		public:
			Identifier(int lineNumber, const char* identifierName);
		
			void accept(Visitor visitor);
			Type* accept(TypeVisitor typeVisitor);
			
			std::string toString() const;
		
		private:
			std::string identifierName;
	};
}

#endif
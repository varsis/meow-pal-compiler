#ifndef IDENTIFIER_TYPE
#define IDENTIFIER_TYPE

#include <string>
#include "Type.hpp"
#include "ASTNode.hpp"

namespace Meow
{
	class Visitor;
	class TypeVisitor;

	class IdentifierType : public Type
	{
		public:
			IdentifierType(unsigned int lineNumber, const char* identiferTypeName);
			
			virtual void accept(Visitor visitor);
			virtual Type* accept(TypeVisitor typeVisitor);
			std::string toString() const;
			
		private:
			std::string identiferTypeName;
	};
}

#endif

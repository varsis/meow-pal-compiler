#ifndef IDENTIFIER_TYPE
#define IDENTIFIER_TYPE

#include <string>
#include "Type.hpp"
#include "LineNumberInformation.hpp"

class Visitor;
class TypeVisitor;

class IdentifierType : public Type, public LineNumberInformation
{
	public:
		IdentifierType(unsigned int lineNumber, const char* identiferTypeName);
		
		void accept(Visitor vistor);
		Type* accept(TypeVisitor typeVisitor);
		std::string toString() const;
		
	private:
		std::string identiferTypeName;
};

#endif

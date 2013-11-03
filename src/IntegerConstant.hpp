#ifndef INTEGERCONSTANT_HPP
#define INTEGERCONSTANT_HPP

#include "Constant.hpp"
#include "Statement.hpp"
#include "Identifier.hpp"
#include "ASTNode.hpp"

namespace Meow
{
	// Forward Declarations
	//class Visitor;
	//class TypeVisitor;

	class IntegerConstant : public Constant
	{
		public:
			IntegerConstant(int lineNumber, int value);

			//virtual void accept(Visitor visitor);
			//virtual Type accept(TypeVisitor visitor);
	};
}

#endif

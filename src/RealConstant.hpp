#ifndef REALCONSTANT_HPP
#define REALCONSTANT_HPP

#include "Constant.hpp"
#include "Statement.hpp"
#include "Identifier.hpp"
#include "ASTNode.hpp"

namespace Meow
{
	// Forward Declarations
	//class Visitor;
	//class TypeVisitor;

	class RealConstant : public Constant
	{
		public:
			RealConstant(int lineNumber, double value);

			//virtual void accept(Visitor visitor);
			//virtual Type accept(TypeVisitor visitor);
	};
}

#endif

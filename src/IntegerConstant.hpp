#ifndef INTEGERCONSTANT_HPP
#define INTEGERCONSTANT_HPP

#include "Constant.hpp"
#include "Statement.hpp"
#include "Identifier.hpp"
#include "ASTNode.hpp"

namespace Meow
{
	class IntegerConstant : public Constant
	{
		public:
			IntegerConstant(int lineNumber, int value);
	};
}

#endif

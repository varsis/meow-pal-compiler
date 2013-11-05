#ifndef REALCONSTANT_HPP
#define REALCONSTANT_HPP

#include "Constant.hpp"
#include "Statement.hpp"
#include "Identifier.hpp"
#include "ASTNode.hpp"

namespace Meow
{
	class Visitor;

	class RealConstant : public Constant
	{
		public:
			RealConstant(int lineNumber, double value);

		private:
			double m_value;
	};
}

#endif

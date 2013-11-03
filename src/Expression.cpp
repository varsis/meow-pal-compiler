#include <string>
#include "Expression.hpp"
#include "RealConstant.hpp"

namespace Meow
{
	Expression::Expression(std::string* literal)
	{
	}

	Expression::Expression(RealConstant* constant)
	{
	}

	void Expression::accept(Vistor* v)
	{
	}
}

#include "AddExpression.hpp"

namespace Meow
{
	AddExpression::AddExpression(Expression* left, Expression* right)
	: BinaryExpression(left, right)
	{
	}
}

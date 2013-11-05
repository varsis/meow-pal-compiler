#ifndef ADDEXPRESSION_HPP
#define ADDEXPRESSION_HPP

#include "BinaryExpression.hpp"

namespace Meow
{
	// Forward Declarations
	class Visitor;
	class Type;
	
	class AddExpression : public BinaryExpression
	{
		public:
			AddExpression(Expression* left, Expression* right);
	};
}
#endif

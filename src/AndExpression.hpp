#ifndef ANDEXPRESSION_HPP
#define ANDEXPRESSION_HPP

#include "BinaryExpression.hpp"

namespace Meow
{
	// Forward Declarations
	class Visitor;
	class Type;
	
	class AndExpression : public BinaryExpression
	{
		public:
			AndExpression(Expression* left, Expression* right);
		
			virtual void accept(Visitor* visitor);
		
	};
}
		
#endif
		

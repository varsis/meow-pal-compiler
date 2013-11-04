#include "Constant.hpp"
#include "Visitor.hpp"

namespace Meow
{
	void Constant::acceptPreOrder(Visitor* visitor)
	{
		visitor->visit(this);
	}

	void Constant::acceptPostOrder(Visitor* visitor)
	{
		visitor->visit(this);
	}
}

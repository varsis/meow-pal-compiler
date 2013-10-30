#ifndef TYPE_HPP
#define TYPE_HPP

#include "LineNumberInformation.hpp"

// Forward Declarations
class Visitor;
class TypeVisitor;

namespace Meow
{
	class Type : public LineNumberInformation {
		public:
			virtual void accept(Visitor visitor) = 0;
			virtual Type accept(TypeVisitor visitor) = 0;
	};
}

#endif

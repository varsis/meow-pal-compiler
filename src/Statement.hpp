#ifndef STATEMENT_HPP
#define STATEMENT_HPP

#include "LineNumberInformation.hpp"

// Forward Declarations
class Visitor;
class TypeVisitor;

class Statement {
	public:
		virtual void accept(Visitor visitor) = 0;
		virtual Type accept(TypeVisitor visitor) = 0;
};

#endif
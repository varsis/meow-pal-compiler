#ifndef EXPRESSION_H
#define EXPRESSION_H

#include <string>

class Vistor;

namespace Meow
{
	class RealConstant;

	class Expression {
		public:

			Expression(std::string* literal);
			Expression(RealConstant* constant);

			virtual void accept(Vistor* v);
	};
}

#endif

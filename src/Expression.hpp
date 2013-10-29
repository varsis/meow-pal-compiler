#ifndef EXPRESSION_H
#define EXPRESSION_H

class Vistor;

namespace Meow
{
	class Expression {
		public:
			virtual void accept(Vistor v) = 0;
	};
}

#endif

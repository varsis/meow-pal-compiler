#ifndef WHILESTATEMENT_HPP
#define WHILESTATEMENT_HPP

#include "Statement.hpp"

namespace Meow
{
	// Forward Declarations
	class Visitor;
	class Expression;
	class Type;

	class WhileStatement : public Statement
	{
		public:
			WhileStatement(Expression* condition,
				       Statement* loopStatement);

			virtual void acceptPreOrder(Visitor* visitor);
			virtual void acceptPostOrder(Visitor* visitor);

		private: 
			Expression* m_condition;
			Statement* m_loopStatement;

	};
}

#endif

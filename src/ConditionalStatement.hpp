#ifndef CONDITIONALSTATEMENT_HPP
#define CONDITIONALSTATEMENT_HPP

#include "Statement.hpp"

namespace Meow
{
	// Forward Declarations
	class Visitor;
	class Expression;
	class Type;

	class ConditionalStatement : public Statement
	{
		public:
			ConditionalStatement(Expression* condition,
					     Statement* thenStatement,
					     Statement* elseStatement);

			virtual void acceptPreOrder(Visitor* visitor);
			virtual void acceptPostOrder(Visitor* visitor);

		private: 
			Expression* m_condition;
			Statement* m_thenStatement;
			Statement* m_elseStatement;

	};
}

#endif

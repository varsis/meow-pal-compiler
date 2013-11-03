#ifndef WHILESTATEMENT_HPP
#define WHILESTATEMENT_HPP

#include "Statement.hpp"

namespace Meow
{
	// Forward Declarations
	class Visitor;
	class TypeVisitor;
	class Expression;
	class Type;

	class WhileStatement : public Statement
	{
		public:
			WhileStatement(Expression* condition,
					Statement* loopStatement)
				: m_condition(condition)
				, m_loopStatement(loopStatement)
			{
			}

			virtual void accept(Visitor* visitor) { }
			virtual Type* accept(TypeVisitor* visitor) {return 0;}

		private: 
			Expression* m_condition;
			Statement* m_loopStatement;

	};
}

#endif

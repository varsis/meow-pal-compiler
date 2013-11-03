#ifndef CONDITIONALSTATEMENT_HPP
#define CONDITIONALSTATEMENT_HPP

#include "Statement.hpp"

namespace Meow
{
	// Forward Declarations
	class Visitor;
	class TypeVisitor;
	class Expression;
	class Type;

	class ConditionalStatement : public Statement
	{
		public:
			ConditionalStatement(Expression* condition,
					Statement* thenStatement,
					Statement* elseStatement)
				: m_condition(condition)
				, m_thenStatement(thenStatement)
				, m_elseStatement(elseStatement)
			{
			}

			virtual void accept(Visitor* visitor) { }
			virtual Type* accept(TypeVisitor* visitor) {return 0;}

		private: 
			Expression* m_condition;
			Statement* m_thenStatement;
			Statement* m_elseStatement;

	};
}

#endif

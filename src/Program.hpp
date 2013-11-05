#ifndef PROGRAM_HPP
#define PROGRAM_HPP

#include "ASTNode.hpp"
#include "ASTListTypes.hpp"
#include "Visitor.hpp"

namespace Meow
{
	class Type; 
	class Declarations;
	class CompoundStatement;

	class Program : public ASTNode
	{
		public:
			Program(Declarations* declarations, CompoundStatement* statements);

			~Program();
			
			virtual void acceptPreOrder(Visitor* visitor);
			virtual void acceptPostOrder(Visitor* visitor);

			const CompoundStatement* getStatements() const;
			const Declarations* getDeclarations() const;
		
		private:

			Declarations* m_declarations;
			CompoundStatement* m_statements;
	};
}
#endif

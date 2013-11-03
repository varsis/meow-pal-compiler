#ifndef VARIABLEDECLARATION_HPP
#define VARIABLEDECLARATION_HPP

#include <string>
#include <vector>
#include "ASTNode.hpp"

using namespace std;

namespace Meow
{
	class Type;
	class Visitor;
	class TypeVisitor;
	class Identifier;

	class VariableDeclaration : public ASTNode
	{
		public:
			VariableDeclaration(int lineNumber, Type* type)
				: m_type(type)
			{
			}

			~VariableDeclaration();
		
			void accept(Visitor* visitor);
			const Type* accept(TypeVisitor* typeVisitor);

			void addIdentifier(Identifier* id)
			{	
				m_identifiers.push_back(id);
			}

			const vector<Identifier*>* getIdentifiers() const
			{	
				return &m_identifiers;
			}

			const Type* getType() const;
		
		private:
			vector<Identifier*> m_identifiers;
			Type* m_type;
	};
}

#endif

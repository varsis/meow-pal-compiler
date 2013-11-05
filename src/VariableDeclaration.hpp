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
	class Identifier;

	class VariableDeclaration : public ASTNode
	{
		public:
			VariableDeclaration(int lineNumber, Type* type);

			~VariableDeclaration();
		
			virtual void acceptPreOrder(Visitor* visitor);
			virtual void acceptPostOrder(Visitor* visitor);

			void addIdentifier(Identifier* id);

			const vector<Identifier*>* getIdentifiers() const;

			const Type* getType() const;
		
		private:
			vector<Identifier*> m_identifiers;
			Type* m_type;
	};
}

#endif

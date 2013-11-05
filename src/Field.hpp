#ifndef FIELD
#define FIELD

#include <string>
#include <vector>
#include "ASTNode.hpp"

using namespace std;

namespace Meow
{
	class Type;
	class Visitor;
	class Identifier;

	class Field : public ASTNode
	{
		public:
			Field(int lineNumber, Type* type);

			~Field();
		
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

#ifndef PARAMETERLIST_HPP
#define PARAMETERLIST_HPP

#include "ASTNode.hpp"

namespace Meow
{
	class Identifier;
	class Visitor;
	class Type;
	class TypeVisitor;

	class ParameterList : public ASTNode
	{
		public:
			ParameterList(int lineNumber)
			{
			}
		
			void accept(Visitor* visitor);
			const Type* accept(TypeVisitor* typeVisitor);
		
		private:
			//vector<Parameter>* m_parameters;
	};
}

#endif

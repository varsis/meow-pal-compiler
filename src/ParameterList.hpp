#ifndef PARAMETERLIST_HPP
#define PARAMETERLIST_HPP

#include <vector>

#include "ASTNode.hpp"
#include "Parameter.hpp"

namespace Meow
{
	class Identifier;
	class Visitor;
	class Type;

	class ParameterList : public ASTNode
	{
		public:
			ParameterList(int lineNumber);

			void addParameter(Parameter* param);

			const std::vector<Parameter*>* getParameters() const;
		
			void accept(Visitor* visitor);
		
		private:
			std::vector<Parameter*> m_parameters;
	};
}

#endif

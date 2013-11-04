#include "ParameterList.hpp"

namespace Meow
{
	ParameterList::ParameterList(int lineNumber)
	{
	}
	
	void ParameterList::addParameter(Parameter* param)
	{
		m_parameters.push_back(param);
	}
	
	const std::vector<Parameter*>* ParameterList::getParameters() const
	{
		return &m_parameters;
	}
	
	void ParameterList::accept(Visitor* visitor)
	{
	}
	
	const Type* ParameterList::accept(TypeVisitor* typeVisitor)
	{
	}
	
}

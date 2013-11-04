#include "ParameterList.hpp"
#include "Visitor.hpp"
#include "Parameter.hpp"

namespace Meow
{
	ParameterList::ParameterList(int lineNumber)
	{
	}

	void ParameterList::acceptPreOrder(Visitor* visitor)
	{
		visitor->visit(this);

		std::vector<Parameter*>::iterator it;
		for (it = m_parameters.begin(); it != m_parameters.end(); ++it)
		{
			(*it)->acceptPreOrder(visitor);
		}
	}

	void ParameterList::acceptPostOrder(Visitor* visitor)
	{
		std::vector<Parameter*>::iterator it;
		for (it = m_parameters.begin(); it != m_parameters.end(); ++it)
		{
			(*it)->acceptPostOrder(visitor);
		}

		visitor->visit(this);
	}
	
	void ParameterList::addParameter(Parameter* param)
	{
		m_parameters.push_back(param);
	}
	
	const std::vector<Parameter*>* ParameterList::getParameters() const
	{
		return &m_parameters;
	}
}

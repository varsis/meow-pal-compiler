#include "Symbol.hpp"
#include <string>

namespace Meow
{
	void Symbol::setName(std::string name)
	{
		m_name = name;
	}

	void Symbol::setType(std::string type)
	{
		m_type = type;
	}

	std::string Symbol::getName()
	{
		return m_name;
	}

	std::string Symbol::getType()
	{
		return m_type;
	}

}


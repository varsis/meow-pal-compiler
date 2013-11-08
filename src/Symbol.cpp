#include "Symbol.hpp"
#include <string>

namespace Meow
{
	Symbol::Symbol()
		: m_lexicalLevel(-1)
		, m_type(NULL)
		, m_sizeInMem(-1)
		, m_location(-1)
		, m_declLineno(-1)
		, m_initialized(false)
		, m_procedureClass(UserDefined)
	{
	}

	Symbol::Symbol(std::string name, Symbol::SymbolType type)
		: m_name(name)
		, m_symbolType(type)
		, m_lexicalLevel(-1)
		, m_type(NULL)
		, m_sizeInMem(-1)
		, m_location(-1)
		, m_declLineno(-1)
		, m_initialized(false)
		, m_procedureClass(UserDefined)
	{
	}
		
	void Symbol::setName(std::string name)
	{
		m_name = name;
	}

	void Symbol::setSymbolType(SymbolType type)
	{
		m_symbolType = type;
	}

	void Symbol::setType(Type* type)
	{
		m_type = type;
	}

	void Symbol::setLexLevel(int level)
	{
		m_lexicalLevel = level;
	}

	void Symbol::setSizeInMem(int size)
	{
		m_sizeInMem = size;
	}

	void Symbol::setLocation(int loc)
	{
		m_location = loc;
	}

	void Symbol::setDeclLineno(int line)
	{
		m_declLineno = line;
	}

	void Symbol::setInitialized()
	{
		m_initialized = true;
	}

	void Symbol::addParameter(Parameter parameter)
	{
		m_parameters.push_back(parameter);
	}

	std::string Symbol::getName()
	{
		return m_name;
	}

	Symbol::SymbolType Symbol::getSymbolType()
	{
		return m_symbolType;
	}

	Type* Symbol::getType()
	{
		return m_type;
	}

	int Symbol::getLexLevel()
	{
		return m_lexicalLevel;
	}

	int Symbol::getSizeInMem()
	{
		return m_sizeInMem;
	}

	int Symbol::getLocation()
	{
		return m_location;
	}

	int Symbol::getDeclLineno()
	{
		return m_declLineno;
	}

	bool Symbol::getInitialized()
	{
		return m_initialized;
	}

	unsigned int Symbol::getParameterCount() const
	{
		return m_parameters.size();
	}

	ParameterList Symbol::getParameters() const
	{
		return m_parameters;
	}

	Parameter* Symbol::getParameter(std::string name) 
	{
		ParameterList::iterator it = m_parameters.begin();

		for (; it != m_parameters.end(); it++)
		{
			if ((*it).id.compare(name) == 0)
			{
				return &(*it);
			}
		}

		return NULL;
	}
}


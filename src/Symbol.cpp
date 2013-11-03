#include "Symbol.hpp"
#include <string>

namespace Meow
{
	Symbol::Symbol()
	{
		m_name = "";
		m_symbolType = "";
		m_type = "";
		m_lexicalLevel = -1;
		m_sizeInMem = -1;
		m_location = -1;
		m_returnType = "";
		m_declLineno = -1;
		m_initialized = false;
	}

	Symbol::Symbol(std::string name, std::string symbolType, int level)
	{
		m_name = name;
		m_symbolType = symbolType;
		m_type = "";
		m_lexicalLevel = level;
		m_sizeInMem = -1;
		m_location = -1;
		m_returnType = "";
		m_declLineno = -1;
		m_initialized = false;
	}
		
	void Symbol::setName(std::string name)
	{
		m_name = name;
	}

	void Symbol::setSymbolType(std::string type)
	{
		m_symbolType = type;
	}

	void Symbol::setType(std::string type)
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

	void Symbol::setReturnType(std::string type)
	{
		m_returnType = type;
	}

	void Symbol::setDeclLineno(int line)
	{
		m_declLineno = line;
	}

	void Symbol::setInitialized()
	{
		m_initialized = true;
	}

	std::string Symbol::getName()
	{
		return m_name;
	}

	std::string Symbol::getSymbolType()
	{
		return m_symbolType;
	}

	std::string Symbol::getType()
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

	std::string Symbol::getReturnType()
	{
		return m_returnType;
	}

	int Symbol::getDeclLineno()
	{
		return m_declLineno;
	}

	bool Symbol::getInitialized()
	{
		return m_initialized;
	}

}


#include "Symbol.hpp"
#include "Type.hpp"
#include <string>

using namespace std;

namespace Meow
{
	Symbol::Symbol()
		: m_name("")
		, m_symbolType()
		, m_lexicalLevel(-1)
		, m_type(NULL)
		, m_sizeInMem(-1)
		, m_location(-1)
		, m_declLineno(-1)
		, m_initialized(false)
		, m_label("")
		, m_procedureClass(UserDefined)
		, m_parameterSpace(0)
		, m_varParam(false)
	{
	}
	
	Symbol::Symbol(std::string name, Symbol::SymbolType type)
		: m_name(name)
		, m_symbolType(type)
		, m_lexicalLevel(-1)
		, m_type(NULL)
		, m_sizeInMem(1)
		, m_location(-1)
		, m_declLineno(-1)
		, m_initialized(false)
		, m_label("")
		, m_procedureClass(UserDefined)
		, m_parameterSpace(0)
		, m_varParam(false)
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

	Symbol* Symbol::addParameter(std::string id, Type* type, bool var, int offset)
	{
		Symbol* param = new Symbol(id, Symbol::VariableSymbol);

		if (type)
		{
			param->setType(type);
			param->setSizeInMem(type->getTypeSize());
			param->setLocation(-3 - m_parameterSpace + offset); // TODO assume a return val?
			param->setVarParam(var);
		}

		m_parameters.push_back(param);

		return param;
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

	const vector<Symbol*>* Symbol::getParameters() const
	{
		return &m_parameters;
	}

	Symbol* Symbol::getParameter(std::string name) 
	{
		vector<Symbol*>::iterator it = m_parameters.begin();

		for (; it != m_parameters.end(); it++)
		{
			if ((*it)->getName().compare(name) == 0)
			{
				return (*it);
			}
		}

		return NULL;
	}
}


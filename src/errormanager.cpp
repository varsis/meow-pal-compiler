#include "errormanager.hpp"

using namespace Meow;

ErrorManager::ErrorManager()
{
}

ErrorManager::~ErrorManager()
{
    for (unsigned int i = 0; i < m_errors.size(); i++)
    {
        delete m_errors.at(i);
    }
}

const std::vector<Error*>& ErrorManager::getErrors() const
{
    return m_errors;
}

void ErrorManager::addError(Error* inputError)
{
    m_errors.push_back(inputError);
}

void ErrorManager::printErrors() const 
{
    for (unsigned int i = 0; i < getErrors().size(); i++)
    {
        getErrors().at(i)->printError();
    }
}

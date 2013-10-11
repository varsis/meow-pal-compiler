#include "errormanager.hpp"

using namespace Meow;

ErrorManager::ErrorManager()
{
    m_errors = new std::vector<Error*>();
}

ErrorManager::~ErrorManager()
{
    for (unsigned int i = 0; i < m_errors->size(); i++)
    {
        delete m_errors->at(i);
    }

    delete m_errors;
}

const std::vector<Error*> * ErrorManager::getErrors() const
{
    return m_errors;
}

void ErrorManager::addError(Error* inputError)
{
    m_errors->push_back(inputError);
}

void ErrorManager::printErrors() const 
{
    const std::vector<Error*> * errors = getErrors();
    for (unsigned int i = 0; i < errors->size(); i++)
    {
        errors->at(i)->printError();
    }
}

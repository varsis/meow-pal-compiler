#include "errormanager.hpp"

using namespace Meow;
bool error_ptr_less( Error *lhs, Error *rhs ) {
        return (lhs->getLineNumber() < rhs->getLineNumber());
}

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

const std::vector<Error*>* ErrorManager::getErrors() const
{
        return &m_errors;
}


void ErrorManager::addError(Error* inputError)
{
        m_errors.push_back(inputError);
        std::sort(m_errors.begin(), m_errors.end(), error_ptr_less);
}

void ErrorManager::printErrors() const
{
    for (unsigned int i = 0; i < getErrors()->size(); i++)
    {
        getErrors()->at(i)->printError();
    }
}

#include "errormanager.hpp"

using namespace Meow;

ErrorManager::ErrorManager()
{
    m_errors  = new std::vector<Error>();
}

std::vector<Error> * ErrorManager::getErrors() {
    return m_errors;
}

void ErrorManager::addError(Error inputError) {
    getErrors()->push_back(inputError);
}

void ErrorManager::printErrors() {
    
    std::vector<Error> * errors = getErrors();
    for ( int i = 0; i < errors->size(); i++)
    {
        Error error = errors->at(i);
        error.printError();
    }

}

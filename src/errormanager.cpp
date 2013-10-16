#include "errormanager.hpp"

namespace Meow
{
        ErrorManager::ErrorManager()
        {
        }

        ErrorManager::~ErrorManager()
        {
                std::multiset<Error*>::iterator it;
                for (it = m_errors.begin(); it != m_errors.end(); ++it)
                {
                        delete *it;
                }
        }

        const std::multiset<Error*>* ErrorManager::getErrors() const
        {
                return &m_errors;
        }


        void ErrorManager::addError(Error* inputError)
        {
                m_errors.insert(inputError);
        }

        void ErrorManager::printErrors() const
        {
                std::multiset<Error*>::iterator it;
                for (it = m_errors.begin(); it != m_errors.end(); ++it)
                {
                        (*it)->printError();
                }
        }
}

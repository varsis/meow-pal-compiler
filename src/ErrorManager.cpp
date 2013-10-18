#include "ErrorManager.hpp"

namespace Meow
{
        ErrorManager::ErrorManager()
        {
                m_errorFlag = false;       
        }

        ErrorManager::~ErrorManager()
        {
                std::multiset<Error*,classcomp>::iterator it;
                for (it = m_errors.begin(); it != m_errors.end(); ++it)
                {
                        delete *it;
                }
        }

        const std::multiset<Error*,classcomp>* ErrorManager::getErrors() const
        {
                return &m_errors;
        }


        void ErrorManager::addError(Error* inputError)
        {
                m_errors.insert(inputError);
                m_errorFlag = true;
        }

        void ErrorManager::printErrors() const
        {
                std::multiset<Error*,classcomp>::iterator it;
                for (it = m_errors.begin(); it != m_errors.end(); ++it)
                {
                        (*it)->printError();
                }
        }
     
        bool ErrorManager::getErrorFlag() const 
        {
                return m_errorFlag;
        }
        
        void ErrorManager::setErrorFlag() 
        {
                m_errorFlag = true;
        }
}

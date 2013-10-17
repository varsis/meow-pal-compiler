#include <iostream>
#include <string>
#include <set>
#include <algorithm>
#include "Error.hpp"

#ifndef ERRORMANAGER_H
#define ERRORMANAGER_H

namespace Meow
{
    class ErrorManager
    {
        public:
            ErrorManager();
            ~ErrorManager();
            void printErrors() const;
            void addError(Error* inputError);
            bool getErrorFlag() const;
            const std::multiset<Error*>* getErrors() const;
            void setErrorFlag();
        private:
            std::multiset<Error*> m_errors;
            bool m_errorFlag;
    };
}

#endif

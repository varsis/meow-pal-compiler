#include <iostream>
#include <string>
#include <set>
#include <algorithm>
#include "error.hpp"

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
            const std::multiset<Error*>* getErrors() const;
            
        private:
            std::multiset<Error*> m_errors;
    };
}

#endif

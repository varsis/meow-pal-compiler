#include <iostream>
#include <string>
#include <vector>
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
            const std::vector<Error*>* getErrors() const;
            
        private:
            std::vector<Error*> m_errors;
    };
}

#endif

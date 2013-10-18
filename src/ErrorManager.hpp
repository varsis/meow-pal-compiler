#include <iostream>
#include <string>
#include <set>
#include <algorithm>
#include "Error.hpp"

#ifndef ERRORMANAGER_H
#define ERRORMANAGER_H

namespace Meow
{
	
	struct classcomp {
		bool operator() (const Error* lhs, const Error* rhs) const
		{return lhs->getLineNumber()<rhs->getLineNumber();}
	};
    class ErrorManager
    {
        public:
            ErrorManager();
            ~ErrorManager();
            void printErrors() const;
            void addError(Error* inputError);
            bool getErrorFlag() const;
            const std::multiset<Error*,classcomp>* getErrors() const;
            void setErrorFlag();
        private:
            std::multiset<Error*,classcomp> m_errors;
            bool m_errorFlag;
    };
}

#endif

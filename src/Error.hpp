#ifndef ERROR_H
#define ERROR_H

#include <iostream>
#include <string>
#include "ErrorCodes.hpp"

namespace Meow
{
    class Error
    {
        public:
            Error(std::string inputString);
            Error(std::string inputString, unsigned int inputLine);
            Error(ErrorCode errorCode, std::string inputString, unsigned int inputLine);

            bool operator < (Error* other) const
            {
                return getLineNumber() < other->getLineNumber();
            }

            std::string getErrorString() const;
            ErrorCode getErrorCode() const;
            unsigned int getLineNumber() const;
            void printError();


        private:
            void setErrorString(std::string);
            void setLineNumber(unsigned int line);
            static const int NOLINENUMBER = -1;

            ErrorCode m_errorCode;
            std::string m_errorString;
            unsigned int m_lineNumber;
    };
}

#endif

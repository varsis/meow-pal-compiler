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
            Error(std::string inputString, int inputLine);
            Error(ErrorCode errorCode, std::string inputString, int inputLine);

            std::string getErrorString() const;
            ErrorCode getErrorCode() const;
            int getLineNumber() const;
            void printError();

            static const int NoLineNumber = -1;

        private:
            void setErrorString(std::string);
            void setLineNumber(int line);

            ErrorCode m_errorCode;
            std::string m_errorString;
            int m_lineNumber;
    };
}

#endif

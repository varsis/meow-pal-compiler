#ifndef Included_ERROR_H
#define Included_ERROR_H

#include <iostream>
#include <string>
#include "errorcodes.hpp"

namespace Meow
{

class Error
    {
public:
    Error(std::string);
    Error(std::string, int);
    std::string getErrorString() const;
    int getLineNumber() const;
    void printError();

private:
    
    std::string m_errorString;
    int m_lineNumber;
        
    void setErrorString(std::string);
    void setLineNumber(int);
    static const int NOLINENUMBER = -1;
    
    

            };
    
}

#endif
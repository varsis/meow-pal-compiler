#include "error.hpp"
using namespace Meow;

Error::Error(std::string inputString)
{
    setLineNumber(NOLINENUMBER);
    setErrorString(inputString);
}

Error::Error(std::string inputString, int inputLine)
{
    setErrorString(inputString);
    setLineNumber(inputLine);
}

void Error::setLineNumber(int inputLine)
{
    m_lineNumber = inputLine;
}

void Error::setErrorString(std::string inputString)
{
    m_errorString = * new std::string(inputString);
}

std::string Error::getErrorString() const
{
    return m_errorString;
}

int Error::getLineNumber() const
{
    return m_lineNumber;
}

void Error::printError() {
    std::cout << "ERROR -- " << getErrorString() <<  " Line: " << getLineNumber() << "\n";
}


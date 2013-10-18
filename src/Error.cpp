#include "Error.hpp"
using namespace Meow;

Error::Error(std::string inputString)
    : m_errorCode(OtherError)
    , m_errorString(inputString)
    , m_lineNumber(NOLINENUMBER)
{
}

Error::Error(std::string inputString, unsigned int inputLine)
    : m_errorCode(OtherError)
    , m_errorString(inputString)
    , m_lineNumber(inputLine)
{
}

Error::Error(ErrorCode errorCode, std::string inputString, unsigned int inputLine)
    : m_errorCode(errorCode)
    , m_errorString(inputString)
    , m_lineNumber(inputLine)
{
}

void Error::setLineNumber(unsigned int inputLine)
{
    m_lineNumber = inputLine;
}

void Error::setErrorString(std::string inputString)
{
    m_errorString = inputString;
}

ErrorCode Error::getErrorCode() const
{
    return m_errorCode;
}

std::string Error::getErrorString() const
{
    return m_errorString;
}

unsigned int Error::getLineNumber() const
{
    return m_lineNumber;
}

void Error::printError() {
    std::cout << "ERROR -- (Line " << getLineNumber() << ") : " << getErrorString() << "\n";
}



#include <iostream>
#include <string>
#include <vector>
#include "error.hpp"

namespace Meow
{
    
class ErrorManager
    {
public:
    ErrorManager();
    void printErrors();
    void addError(Error);

    
private:
    std::vector<Error> * m_errors;
    std::vector<Error> * getErrors();
            };
}


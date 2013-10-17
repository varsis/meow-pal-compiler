#include <string>
#include <fstream>
#include "Parser.hpp"
#include "Scanner.hpp"
#include "errormanager.hpp"
#include "pal.tab.h"

namespace Meow
{

    Parser::Parser(ErrorManager* manager)
        : m_errorManager(manager)
    {
    }

    int Parser::parseFile(std::ifstream* fileStream)
    {
        int retval;
        PalScanner scanner(fileStream, m_errorManager);
        PalParser parser(scanner, *m_errorManager);

        retval = parser.parse();
        
        if (retval != 0) 
        {
          m_errorManager->setErrorFlag();
        }

        return retval;
    }

    int Parser::parseFile(std::string fileName)
    {
        std::ifstream fileStream(fileName.c_str());

        if (fileStream == NULL || !fileStream.is_open())
        {
                std::cerr << "** Error: Unable to open" << fileName << "\n";
                return -1;
        }

        return parseFile(&fileStream);
    }
}

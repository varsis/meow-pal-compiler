#include <string>
#include <fstream>
#include "Parser.hpp"
#include "Scanner.hpp"
#include "ErrorManager.hpp"
#include "pal.tab.h"

namespace Meow
{
	Parser::Parser(ErrorManager* manager, bool debugFlag)
	    : m_errorManager(manager),
	      m_debugFlag(debugFlag)
	{
	}

	int Parser::parseFile(std::ifstream* fileStream)
	{
		int retval;
		PalScanner scanner(fileStream, m_errorManager);

		PalParser parser(scanner, *m_errorManager);
		if(m_debugFlag)
		{
			parser.set_debug_level(1);
		}

		retval = parser.parse();

		// Parser might have signaled an error and given up,
		// but we can keep running scanner to the EOF to find more lexical errors
		PalParser::semantic_type yylval;
		while (scanner.yylex(&yylval));

		if (retval != 0) 
		{
			m_errorManager->setErrorFlag();
		}

		return (int) m_errorManager->getErrorFlag();
	}

	int Parser::parseFile(std::string fileName)
	{
		std::ifstream fileStream(fileName.c_str());

		if (fileStream == NULL || !fileStream.is_open())
		{
			std::cerr << "** Error: Unable to open" 
			    << fileName << "\n";
			return -1;
		}

		return parseFile(&fileStream);
	}
}

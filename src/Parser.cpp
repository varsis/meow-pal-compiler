#include <string>
#include <fstream>
#include "Parser.hpp"
#include "Scanner.hpp"
#include "ErrorManager.hpp"
#include "SymbolTable.hpp"
#include "SemanticHelper.hpp"
#include "AscHelper.hpp"
#include "pal.tab.hpp"

namespace Meow
{
	Parser::Parser(ErrorManager* manager)
	    : m_errorManager(manager),
	      m_debugFlag(false)
	{
	}

	void Parser::setDebugFlag(bool value)
	{
		m_debugFlag = value;
	}

	void Parser::setArrayBoundsFlag(bool value)
	{
		m_arrayBoundsFlag = value;
	}

	int Parser::parseFile(std::ifstream* palInput, std::ofstream* ascOutput)
	{
		int retval;
		SymbolTable symbolTable;
		
		PalScanner scanner(palInput, m_errorManager, &symbolTable);

		SemanticHelper semanticHelper(&scanner, m_errorManager, &symbolTable);
		semanticHelper.addPredefinedSymbols();

		AscHelper ascHelper(*ascOutput, &symbolTable, &semanticHelper,
				m_arrayBoundsFlag);

		PalParser parser(scanner, *m_errorManager, symbolTable, semanticHelper, ascHelper);

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

	int Parser::parseFile(std::string inputFile, std::string outputFile)
	{
		std::ifstream palInput(inputFile.c_str());

		std::ofstream ascOutput;
		ascOutput.open(outputFile.c_str(), ofstream::out | ofstream::trunc);

		if (palInput == NULL || !palInput.is_open())
		{
			std::cerr << "** Error: Unable to open" 
			    << inputFile << "\n";
			return -1;
		}


		if (ascOutput == NULL || !ascOutput.is_open())
		{
			std::cerr << "** Error: Unable to open" 
			    << ascOutput << "\n";
			return -1;
		}

		return parseFile(&palInput, &ascOutput);
	}
}

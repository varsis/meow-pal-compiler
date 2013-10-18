#include <unistd.h>
#include <fstream>
#include <iostream>
#include <cstdlib>

#include "Compiler.hpp"
#include "Parser.hpp"

using namespace Meow;

Compiler::Compiler()
	: m_parser(&m_errorManager),
	  m_leaveASC(false),
	  m_programListing(true), 
	  m_runtimeArrayBoundChecking(true),
	  m_debug(false)
{
}

Compiler::~Compiler()
{
}

void Compiler::displayUsage()
{
	std::cout << "\nProgram Usage: pal [-n] file.pal\n\n";
	std::cout << "OPTIONS:\n";
	std::cout << "\t-n : Do not produce a program listing. Default is" 
		  << "to produce one.\n";
	std::cout << "\t-d : Enable bison debug mode.\n";
	std::cout << std::endl;
}

void Compiler::getArguments(int argc, char* argv[])
{
	int opt = 0;
	const char* optString = "nd";
	
	if (argc == 1)
	{
		displayUsage();
		std::exit(-1);
	}
	
	opt = getopt(argc, argv, optString);
	
	while (opt != -1)
	{
		switch (opt)
		{
			case 'n':
				m_programListing = false;
				break;
			case 'd':
				m_debug = true;
				break;
			default:
				std::cerr << "\n* Unrecognized option: -" 
				    << opt << "\n";
				displayUsage();
				std::exit(-1);	
		}
		
		opt = getopt(argc, argv, optString);
	}
	
	if ( (argc - optind) == 0)
	{
		std::cerr << "\n* No input file specified.\n";
		displayUsage();
		std::exit(-1);
	}
	
	m_inputFileName = argv[optind];
}

void Compiler::printErrors()
{
	const ErrorList* errors = m_errorManager.getErrors();
	ErrorList::const_iterator errorIt;

	for (errorIt = errors->begin(); errorIt != errors->end(); ++errorIt)
	{
		(*errorIt)->printError();
	}
}

void Compiler::printProgramListing()
{
	const ErrorList* errors = m_errorManager.getErrors();
	std::ifstream inputFileStream(m_inputFileName.c_str());

	int lineCount = 1;
	std::string currentLine;
	ErrorList::const_iterator errorIt;

	// open file
	if (!inputFileStream.is_open())
	{
		std::cerr << "** Error: Unable to find " << m_inputFileName << "\n";
	}
	else
	{
		errorIt = errors->begin(); 

		while (std::getline(inputFileStream, currentLine))
		{
			// print the line
			std::cout << lineCount << ":\t" << currentLine 
			    << std::endl;

			// print any errors for the line
			// assumes errors are sorted by line number
			while (errorIt != errors->end() && 
			    (*errorIt)->getLineNumber() == lineCount)
			{
				(*errorIt)->printError();
				++errorIt;
			}
			lineCount++;
		}

		// Print any leftover errors with no associated line number
		// (will be sorted to end)
		while (errorIt != errors->end())
		{
			(*errorIt)->printError();
			++errorIt;
		}

		if (m_errorManager.getErrorFlag()) 
		{
			std::cout << "pal: *** " << m_inputFileName 
			    << " has " << errors->size() << " errors.\n";
		}

		inputFileStream.close();
	}
}

int Compiler::run(int argc, char* argv[])
{
	int parseResult = 0;

	getArguments(argc, argv);

	m_parser.setDebugFlag(m_debug);

	parseResult = m_parser.parseFile(m_inputFileName);

	if (m_programListing)
	{
		printProgramListing();
	}
	else
	{
		printErrors();
	}

	return parseResult;
}

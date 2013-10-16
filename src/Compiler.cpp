#include <unistd.h>
#include <fstream>
#include <iostream>
#include <cstdlib>

#include "ProgramListing.hpp"
#include "Compiler.hpp"
#include "Parser.hpp"

using namespace Meow;

Compiler::Compiler()
	: m_parser(&m_errorManager), 
	  m_leaveASC(false), 
	  m_programListing(true), 
	  m_runtimeArrayBoundChecking(true)
{
}

Compiler::~Compiler()
{
}

void Compiler::displayUsage()
{
	std::cout << "\nProgram Usage: pal [-S] [-n] [-a] file.pal\n\n";
	std::cout << "OPTIONS:\n";
	std::cout << "\t-S : Leave Asc code in file.asc instead of removing it.\n";
	std::cout << "\t-n : Do not produce a program listing. Default is to produce one.\n";
	std::cout << "\t-a : Do not generate run-time array subscript bounds checking. Default\n";
	std::cout << "\t     is to do the checking.\n\n";
}

void Compiler::getArguments(int argc, char* argv[])
{
	int opt = 0;
	const char* optString = "Sna";
	
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
			case 'S':
				m_leaveASC = true;
				break;
			case 'n':
				m_programListing = false;
				break;
			case 'a':
				m_runtimeArrayBoundChecking = false;
				break;
			default:
				std::cerr << "\n* Unrecognized option: -" << opt << "\n";
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

void Compiler::printProgramListing()
{
	new Meow::ProgramListing(m_inputFileName,&m_errorManager);
}

void Compiler::removeAscOutput()
{
	std::cout << "Remove Asc output file.\n";
}

int Compiler::run(int argc, char* argv[])
{
	Parser parser(&m_errorManager);
	int parseResult = 0;
	
	getArguments(argc, argv);
	
	if (!m_leaveASC)
		removeAscOutput();
	
	parseResult = parser.parseFile(m_inputFileName);
        
        if (m_programListing)
		printProgramListing();

	return parseResult;
}

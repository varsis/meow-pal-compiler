#include <unistd.h>
#include <fstream>
#include <iostream>
#include <cstdlib>

#include "Scanner.hpp"
#include "Compiler.hpp"
#include "pal.tab.h"
using namespace Meow;

Compiler::Compiler()
	: m_leaveASC(false), 
	  m_programListing(true), 
	  m_runtimeArrayBoundChecking(true)
{
}

Compiler::~Compiler()
{
	if (m_scanner != NULL)
	{
		delete m_scanner;
		m_scanner = NULL;
	}
	
	if (m_parser != NULL)
	{
		delete m_parser;
		m_parser = NULL;
	}
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
	std::cout << "Print program listing.\n";
}

void Compiler::removeAscOutput()
{
	std::cout << "Remove Asc output file.\n";
}

int Compiler::run(int argc, char* argv[])
{
	std::ifstream* inputFileStream = NULL;
	int parseResult = 0;
	
	getArguments(argc, argv);
	
	if (!m_leaveASC)
		removeAscOutput();
	
	if (m_programListing)
		printProgramListing();
	
	inputFileStream = new std::ifstream(m_inputFileName.c_str());
	
	if (inputFileStream == NULL || !inputFileStream->is_open())
	{
		std::cerr << "** Error: Unable to find" << m_inputFileName << "\n";
		return -1;
	}
	
	m_scanner = new PalScanner(inputFileStream, &m_errorManager);
	m_parser = new PalParser(*m_scanner);
	
	parseResult = m_parser->parse();
	
	inputFileStream->close();
	delete inputFileStream;
	inputFileStream = NULL;
	
	return parseResult;
}

#include <unistd.h>
#include <fstream>
#include <iostream>
#include <cstdlib>
#include <stdio.h>
#include <unistd.h>

#include "Compiler.hpp"
#include "Parser.hpp"

using namespace Meow;

Compiler::Compiler()
	: m_parser(&m_errorManager),
	  m_leaveASC(false),
	  m_programListing(true), 
	  m_runtimeArrayBoundChecking(true),
	  m_debug(false),
	  m_printStdout(false)
{
}

Compiler::~Compiler()
{
}

void Compiler::displayUsage()
{
	std::cout << "\nProgram Usage: pal [-ndp] file.pal\n\n";
	std::cout << "OPTIONS:\n";
	std::cout << "\t-n : Do not produce a program listing. Default is" 
		  << "to produce one.\n";
	std::cout << "\t-d : Enable bison debug mode.\n";
	std::cout << "\t-p : Print program listing to stdout instead of file.\n";
	std::cout << std::endl;
}

void Compiler::getArguments(int argc, char* argv[])
{
	int opt = 0;
	const char* optString = "ndp";

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
			case 'p':
				m_printStdout = true;
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

	m_ascExecutable = getExecPath(argv[0]) + "asc";
	
	m_inputFileName = argv[optind];

	if(m_inputFileName.find_last_of(".") > m_inputFileName.find_last_of("/")) 
	{
		std::string name = m_inputFileName.substr(0,
			m_inputFileName.find_last_of("."));
		m_listingFile = name + ".lst";
		m_ascOutput = name + ".asc";
	}
	else 
	{
		m_listingFile = m_inputFileName + ".lst";
		m_ascOutput = m_inputFileName + ".asc";
	}
}

std::string Compiler::getExecPath(std::string invokeString)
{
	// if argv[0] single word
	if (invokeString.find_last_of('/') == std::string::npos)
	{
		// search in PATH
		char* path_list = strdup(getenv("PATH"));
		char* path = path_list;

		while ((path_list = strchr(path_list, ':')) != NULL)
		{
			path_list[0] = 0;

			// look for pal in path directory
			std::string lscmd("ls ");
			lscmd += path;

			if (*(strchr(path, 0) - 1) != '/')
			{
				lscmd += "/";
			}

			lscmd += invokeString;
			lscmd += " >/dev/null";
			lscmd += " 2>/dev/null";
			if (system(lscmd.c_str()) == 0)
			{
				// pal is in here
				return std::string(path);
			}

			path = path_list + 1;
			path_list = path;
		}
	}

	// if absolute path
	if (invokeString[0] == '/')
	{
		return invokeString.substr(0, invokeString.find_last_of("/"));
	}
	// if relative path, use current working directory
	else
	{
		char buf[1024];
		getcwd(buf, 1024);
		return std::string(buf) + invokeString.substr(0, invokeString.find_last_of("/") + 1);
	}
}

void Compiler::printErrors()
{
	const ErrorList* errors = m_errorManager.getErrors();
	ErrorList::const_iterator errorIt;
	
	for (errorIt = errors->begin(); errorIt != errors->end(); ++errorIt)
	{
		(*errorIt)->printError();
	}
	
	if (m_errorManager.getErrorFlag()) 
	{
		std::cout << "pal: *** " << m_inputFileName 
		<< " has " << errors->size() << " errors.\n";
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
		std::ofstream outputFileStream;
		std::streambuf *coutbuf;
		
		if (!m_printStdout)
		{
			// Redirect cout to file: trick borrowed from StackOverflow
			outputFileStream.open(m_listingFile.c_str());
			coutbuf = std::cout.rdbuf();
			std::cout.rdbuf(outputFileStream.rdbuf());
		}
		errorIt = errors->begin(); 

		while (std::getline(inputFileStream, currentLine))
		{
			// print the line to file
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

		if (!m_printStdout)
		{
			// Reset cout to print to the screen
			std::cout.rdbuf(coutbuf);
			inputFileStream.close();
			outputFileStream.close();
		}
	}

}

int Compiler::run(int argc, char* argv[])
{
	int parseResult = 0;

	getArguments(argc, argv);

	m_parser.setDebugFlag(m_debug);

	parseResult = m_parser.parseFile(m_inputFileName);

	if (m_programListing || m_printStdout)
	{
		printProgramListing();
	}

	if (!m_printStdout)
	{
		printErrors();
	}

	// if no errors, run the generated asc code
	if (parseResult == 0)
	{
		FILE* ascout = popen((m_ascExecutable + " " + m_ascOutput).c_str(), "r");

		pclose(ascout);
	}

	return parseResult;
}

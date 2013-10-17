#include <iostream>
#include <string>
#include <fstream>
#include <set>

#include "ProgramListing.hpp"
#include "errormanager.hpp"
#include "error.hpp"

using namespace Meow;

ProgramListing::ProgramListing(const std::string currentProgram, const ErrorManager * errorManager)
{
	const std::multiset<Error*>* errors = errorManager->getErrors();

	std::ifstream inputFileStream(currentProgram.c_str());

	if (!inputFileStream.is_open())
	{
		std::cerr << "** Error: Unable to find " << currentProgram << "\n";
	}
	else
	{
		unsigned int lineCount = 1;
		std::string currentLine;
 
		std::multiset<Error*>::const_iterator errorIt = errors->begin();

		// open file
		while (std::getline(inputFileStream, currentLine))
		{
			// print the line
			std::cout << lineCount << ": " << currentLine << std::endl;

			// print any errors for the line
			// assumes errors are sorted by line number
			while (errorIt != errors->end() && (*errorIt)->getLineNumber() == lineCount)
			{
				(*errorIt)->printError();
				++errorIt;
			}
			lineCount++;
		}

		// print errors where line number exceeds number of actual lines in the file
		// -> when can this happen?
		// print errors without any line number?
		while (errorIt != errors->end())
		{
			(*errorIt)->printError();
			++errorIt;
		}

  if (errorManager->getErrorFlag()) 
  {
    std::cout << "PROGRAM NOT COMPILED -- CONTAINS ERRORS\n";
  }
  else 
  {
    std::cout << "PROGRAM COMPILED -- NO ERRORS\n";
  }

		inputFileStream.close();
	}

}

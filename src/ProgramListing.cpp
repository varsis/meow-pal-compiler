#include <unistd.h>
#include <fstream>
#include <iostream>
#include <istream>
#include <cstdlib>
#include <string>
#include <iostream>
#include <sstream>
#include <string>
#include <iterator>
#include <fstream>
#include <iomanip>
#include <algorithm>
#include "errormanager.hpp"
#include "error.hpp"
#include "ProgramListing.hpp"

using namespace Meow;



ProgramListing::ProgramListing(const std::string currentProgram, ErrorManager * errorManager)
{
        std::vector<Error*> errors = errorManager->getErrors();
        
        std::ifstream inputFileStream(currentProgram.c_str());
        
	if (!inputFileStream.is_open())
	{
		std::cerr << "** Error: Unable to find " << currentProgram << "\n";
	} else {
                
                int lineCount = 1;
                std::string currentLine;
                // open file
                while (std::getline(inputFileStream, currentLine))
                {
                        std::cout << lineCount << ": " << currentLine << std::endl;
                        
                        while(!errors.empty() && errors.front()->getLineNumber() == lineCount)
                        {
                                errors.front()->printError();
                                errors.erase(errors.begin());
                                
                        }
                        lineCount++;
                }
                
                if(!errors.empty()) {
                        for(int i = 0; i < errors.size(); i++) {
                                errors.at(i)->printError();
                        }
                }
                
                inputFileStream.close();
	}
        
}
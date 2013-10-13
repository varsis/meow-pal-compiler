#ifndef COMPILER_H
#define COMPILER_H

#include <fstream>
#include <string>

#include "errormanager.hpp"

class PalScanner;
class PalParser;

namespace Meow
{
	class Compiler 
	{
	public:
		Compiler();
		virtual ~Compiler();
		int run(int argc, char* argv[]);
	private:
		void getArguments(int argc, char* argv[]);
		void displayUsage();
		void printProgramListing();
		void removeAscOutput();

		ErrorManager m_errorManager;
		std::string m_inputFileName;
		PalScanner* m_scanner;
		PalParser* m_parser;
		bool m_leaveASC;
		bool m_programListing;
		bool m_runtimeArrayBoundChecking;
	};
}

#endif

#ifndef COMPILER_H
#define COMPILER_H

#include <fstream>
#include <string>

#include "Parser.hpp"
#include "ErrorManager.hpp"

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
			void printAST();
			void printProgramListing();
			void printErrors();
			void removeAscOutput();

			ErrorManager m_errorManager;
			Parser m_parser;
			std::string m_inputFileName;
			std::string m_outputFileName;
			bool m_leaveASC;
			bool m_programListing;
			bool m_runtimeArrayBoundChecking;
			bool m_debug;
	};
}

#endif

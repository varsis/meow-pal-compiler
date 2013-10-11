#ifndef COMPILER_H
#define COMPILER_H

#include <fstream>
#include <string>

class Compiler 
{
public:
	Compiler();
	~Compiler();
	int run(int argc, char* argv[]);
private:
	void getArguments(int argc, char* argv[]);
	void displayUsage();
	void printProgramListing();
	void removeAscOutput();

	std::string m_inputFileName;
	bool m_leaveASC;
	bool m_programListing;
	bool m_runtimeArrayBoundChecking;
};

#endif

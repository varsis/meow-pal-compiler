#include "Scanner.hpp"
#include "Parser.hpp"
#include "Compiler.hpp"
using namespace std;

int main(int argc, char* argv[]) {
	Meow::Compiler compiler;
	
	return compiler.run(argc, argv);
}
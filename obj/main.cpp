#include "Scanner.hpp"
#include "Parser.hpp"
using namespace std;

int main(int argc, char** argv) {
	Meow::Parser parser;
	return parser.parse();
}
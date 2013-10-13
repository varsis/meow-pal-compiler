#ifndef PARSER_H
#define PARSER_H

#include <string>
#include <fstream>

namespace Meow
{
	class ErrorManager;

	class Parser
	{
		public:
			Parser(ErrorManager* manager);
		
			int parseFile(std::string fileName);
			int parseFile(std::ifstream* fileStream);
        
		private:
			ErrorManager* m_errorManager;
	};
}

#endif

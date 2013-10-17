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
			Parser(ErrorManager* manager, bool debugFlag = false);
		
			int parseFile(std::string fileName);
			int parseFile(std::ifstream* fileStream);
        
		private:
			ErrorManager* m_errorManager;
			bool m_debugFlag;
	};
}

#endif

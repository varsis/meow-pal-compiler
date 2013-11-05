#ifndef PARSER_H
#define PARSER_H

#include <string>
#include <fstream>

namespace Meow
{
	class ErrorManager;
	class Program;

	struct ParseResult
	{
		Program* program;
	};

	class Parser
	{
		public:
			Parser(ErrorManager* manager);

			int parseFile(std::string fileName);
			int parseFile(std::ifstream* fileStream);

			void setDebugFlag(bool value);

		private:
			ErrorManager* m_errorManager;
			bool m_debugFlag;
	};
}

#endif

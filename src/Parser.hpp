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

			int parseFile(std::string inputFile, std::string outputFile);
			int parseFile(std::ifstream* palInput, std::ofstream* ascOutput);

			void setDebugFlag(bool value);
			void setArrayBoundsFlag(bool value);
			void setLanguageExtensions(bool value);
		private:
			ErrorManager* m_errorManager;
			bool m_debugFlag;
			bool m_arrayBoundsFlag;
			bool m_languageExtensions;
	};
}

#endif

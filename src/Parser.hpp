#ifndef PARSER_H
#define PARSER_H

#include "Scanner.hpp"
#include "errormanager.hpp"
#include "pal.tab.h"


namespace Meow
{
	class Parser
	{
		public:
			Parser(ErrorManager* manager)
				: m_errorManager(manager)
			{
            }
		
			int parseFile(char* fileName)
			{
				return 0;
			}
        
		private:
        
			ErrorManager* m_errorManager;
	};
}

#endif

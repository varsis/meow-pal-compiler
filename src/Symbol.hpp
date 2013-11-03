#ifndef SYMBOL_HPP
#define SYMBOL_HPP

#include <string>

namespace Meow
{
	class Symbol
	{
		private:
			std::string m_name;
			std::string m_symbolType;
			int m_lexicalLevel;		
			std::string m_type;
			int m_sizeInMem;
			int m_location;
			std::string m_returnType;
			int m_declLineno;
			bool m_initialized;

		public:
			Symbol();
			Symbol(std::string, std::string, int);
			void setName(std::string);
			void setSymbolType(std::string);
			void setType(std::string);
			void setLexLevel(int);
			void setSizeInMem(int);
			void setLocation(int);
			void setReturnType(std::string);
			void setDeclLineno(int);
			void setInitialized();

			std::string getName();
			std::string getSymbolType();
			std::string getType();
			int getLexLevel();
			int getSizeInMem();
			int getLocation();
			std::string getReturnType();
			int getDeclLineno();
			bool getInitialized();
	};
}

#endif

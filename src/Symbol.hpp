#ifndef SYMBOL_HPP
#define SYMBOL_HPP

#include <string>

namespace Meow
{
	enum SymbolType
	{
		ConstantSymbol,
		TypeSymbol,
		VariableSymbol,
		ProcedureSymbol
	};

	class Symbol
	{
		public:
			Symbol();
			Symbol(std::string name, SymbolType type);
			void setName(std::string name);
			void setSymbolType(SymbolType type);
			void setType(std::string type);
			void setLexLevel(int);
			void setSizeInMem(int);
			void setLocation(int);
			void setReturnType(std::string returnType);
			void setDeclLineno(int);
			void setInitialized();

			std::string getName();
			SymbolType getSymbolType();
			std::string getType();
			int getLexLevel();
			int getSizeInMem();
			int getLocation();
			std::string getReturnType();
			int getDeclLineno();
			bool getInitialized();

		private:
			std::string m_name;
			SymbolType m_symbolType;
			int m_lexicalLevel;		
			std::string m_type;
			int m_sizeInMem;
			int m_location;
			std::string m_returnType;
			int m_declLineno;
			bool m_initialized;

	};
}

#endif

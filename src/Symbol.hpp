#ifndef SYMBOL_HPP
#define SYMBOL_HPP

#include <string>
#include "Type.hpp"

namespace Meow
{
	class Symbol
	{
		public:

			enum SymbolType
			{
				ConstantSymbol,
				TypeSymbol,
				VariableSymbol,
				ProcedureSymbol,
				FunctionSymbol
			};

			Symbol();
			Symbol(std::string name, SymbolType type);

			void setName(std::string name);
			void setSymbolType(SymbolType type);
			void setType(Type* type);
			void setType(std::string type);
			void setLexLevel(int);
			void setSizeInMem(int);
			void setLocation(int);
			void setReturnType(Type* returnType);
			void setDeclLineno(int);
			void setInitialized();

			std::string getName();
			SymbolType getSymbolType();
			Type* getType();
			int getLexLevel();
			int getSizeInMem();
			int getLocation();
			Type* getReturnType();
			int getDeclLineno();
			bool getInitialized();

		protected:
			std::string m_name;
			SymbolType m_symbolType;
			int m_lexicalLevel;		
			Type* m_type;
			int m_sizeInMem;
			int m_location;
			Type* m_returnType;
			int m_declLineno;
			bool m_initialized;

	};
}

#endif

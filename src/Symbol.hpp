#ifndef SYMBOL_HPP
#define SYMBOL_HPP

#include <string>
#include <vector>
#include "Type.hpp"

namespace Meow
{
	union Value
	{
		int int_val;
		double real_val;
	};

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

			class IdentifierTypePair 
			{
				public:
					IdentifierTypePair(std::string name, Type* type);
					~IdentifierTypePair();

					void setName(std::string name);
					void setType(Type* type);

					std::string getName() const;
					Type* getType() const;

				private:
					std::string m_name;
					Type* m_type;
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

			void addParameter(IdentifierTypePair* typePair);

			std::string getName();
			SymbolType getSymbolType();
			Type* getType();
			int getLexLevel();
			int getSizeInMem();
			int getLocation();
			Type* getReturnType();
			int getDeclLineno();
			bool getInitialized();

			// for procedure/function symbols...
			size_t getParameterCount() const;

			// for constant symbols..
			void setConstantValue(Value v) { m_constValue = v; };
			Value getConstantValue() { return m_constValue; };
			std::vector<IdentifierTypePair*> getParameters() const;
			IdentifierTypePair* getParameter(std::string name);	

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

			// for constant symbols..
			Value m_constValue;


			std::vector<IdentifierTypePair*> m_parameters;

	};

}

#endif

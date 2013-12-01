#ifndef SYMBOL_HPP
#define SYMBOL_HPP

#include <string>
#include <vector>
#include "AuxiliaryTypes.hpp"

namespace Meow
{
	class Type;

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
			void setLexLevel(int);
			void setSizeInMem(int);
			void setLocation(int);
			void setDeclLineno(int);
			void setInitialized();

			std::string getName();
			SymbolType getSymbolType();
			Type* getType();
			int getLexLevel();
			int getSizeInMem();
			int getLocation();
			int getDeclLineno();
			bool getInitialized();

			// for constant symbols..
			void setConstantValue(Value v) { m_constValue = v; };
			void setConstantValue(double v) { m_constValue.real_val = v; };
			void setConstantValue(int v) { m_constValue.int_val = v; };

			Value getConstantValue() { return m_constValue; };

			// for parameters...
			void setVarParam(bool value) { m_varParam = value; };
			bool isVarParam() { return m_varParam; };

			// for procedures + funcitons..
			Symbol* addParameter(std::string id, Type* type, bool var = false, int offset = 0);
			unsigned int getParameterCount() const;
			const std::vector<Symbol*>* getParameters() const;
			Symbol* getParameter(std::string name);	

			int getParameterSpace() { return m_parameterSpace; }
			void allocParameterSpace(int space) { m_parameterSpace += space; }

			void setLabel(std::string label) { m_label = label; }
			std::string getLabel() { return m_label; }

			void setProcClass(ProcedureClass c) { m_procedureClass = c; }
			ProcedureClass getProcClass() { return m_procedureClass; }

		protected:
			std::string m_name;
			SymbolType m_symbolType;
			int m_lexicalLevel;		
			Type* m_type;
			int m_sizeInMem;
			int m_location;
			int m_declLineno;
			bool m_initialized;
			std::string m_label;

			// for constant symbols..
			Value m_constValue;

			// for procedures/functions
			ProcedureClass m_procedureClass;
			std::vector<Symbol*> m_parameters;
			int m_parameterSpace;
			bool m_varParam;

	};

}

#endif

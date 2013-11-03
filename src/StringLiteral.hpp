#ifndef STRINGLITERAL_HPP
#define STRINGLITERAL_HPP 

#include <string>

#include "Constant.hpp"
#include "ASTNode.hpp"

namespace Meow
{
	class StringLiteral : public Constant
	{
		public:
			StringLiteral(int lineNumber, char* value)
				: m_value(value)
			{
			}

			std::string getValue()
			{
				return m_value;
			}

		private:
			std::string m_value;
		
	};
}

#endif

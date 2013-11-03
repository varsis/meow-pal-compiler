#ifndef SYMBOL_HPP
#define SYMBOL_HPP

#include <string>

namespace Meow
{
	class Symbol
	{
		private:
			std::string m_name;
			std::string m_type;
		
		public:
			void setName(std::string);
			void setType(std::string);
			std::string getName();
			std::string getType();
	};
}

#endif

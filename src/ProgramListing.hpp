#ifndef PROGRAMLISTING_H
#define PROGRAMLISTING_H

#include <fstream>
#include <string>
#include "ErrorManager.hpp"

namespace Meow
{
	class ProgramListing
	{
	public:
		ProgramListing(const std::string, Meow::ErrorManager *);
	};
}

#endif

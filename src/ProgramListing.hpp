#ifndef PROGRAMLISTING_H
#define PROGRAMLISTING_H

#include <string>
#include "ErrorManager.hpp"

namespace Meow
{

	class ErrorManager;

	class ProgramListing
	{
		public:
			ProgramListing(const std::string, const ErrorManager *);
	};
}

#endif

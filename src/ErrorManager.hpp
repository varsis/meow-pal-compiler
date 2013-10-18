#include <iostream>
#include <string>
#include <set>
#include <algorithm>
#include "Error.hpp"

#ifndef ERRORMANAGER_H
#define ERRORMANAGER_H

namespace Meow
{
	struct ErrorComparer
	{
		bool operator() (const Error* lhs, const Error* rhs) const
		{
			if (rhs->getLineNumber() == Error::NoLineNumber)
			{
				return 1; // sort errors without lines to end
			}
			return lhs->getLineNumber()<rhs->getLineNumber();
		}
	};

	typedef std::multiset<Error*,ErrorComparer> ErrorList;

	class ErrorManager
	{
		public:
			ErrorManager();
			~ErrorManager();
			void printErrors() const;
			void addError(Error* inputError);
			bool getErrorFlag() const;

			const ErrorList* getErrors() const;

			void setErrorFlag();
		private:
			ErrorList m_errors;
			bool m_errorFlag;
	};
}

#endif

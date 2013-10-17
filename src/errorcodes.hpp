#ifndef ERRORCODES_H
#define ERRORCODES_H

namespace Meow
{
	enum ErrorCode
	{
		OtherError,
		UnclosedComment,
		UnclosedString,
  UnrecognizedSymbol,
  InvalidIdentifier,
  NestedComment,
  UnmatchedComment,
  MissingMethodParentheses,
  MissingProgramParentheses,
  MissingProgramPeriod,
  CStyleAssignment
		/* DECLARE ALL OTHER ERRORS HERE */
	};
}

#endif

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
  MissingProgramParentheses,
  MissingProgramPeriod,
  CStyleAssignment,
  InvalidExpression,
  InvalidProgramHeader,
  InvalidConstDecl
		/* DECLARE ALL OTHER ERRORS HERE */
	};
}

#endif

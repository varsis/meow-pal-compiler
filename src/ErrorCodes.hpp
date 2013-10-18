#ifndef ERRORCODES_H
#define ERRORCODES_H

namespace Meow
{
	enum ErrorCode
	{
		OtherError,
	  	SyntaxError,
		UnclosedComment,
		UnclosedString,
  		UnrecognizedSymbol,
  		InvalidIdentifier,
  		NestedComment,
  		UnmatchedComment,
  		MissingProgramParentheses,
  		MissingProgramPeriod,
  		CStyleAssignment,
  		MismatchedBlock,
  		InvalidExpression,
  		InvalidProgramHeader,
  		InvalidConstDecl,
  		InvalidTypeDecl,
  		InvalidVarDecl,
  		InvalidFunctDecl,
  		InvalidProcDecl
		
		/* DECLARE ALL OTHER ERRORS HERE */
	};
}

#endif
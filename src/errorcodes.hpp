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
	InvalidString,
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
	InvalidProcDecl,
	MultiLineString
		/* DECLARE ALL OTHER ERRORS HERE */
	};
}

#endif

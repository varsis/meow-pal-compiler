#ifndef ERRORCODES_H
#define ERRORCODES_H

namespace Meow
{
	enum ErrorCode
	{
		// Syntax errors
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
		InvalidUpTo,
		InvalidArrayDecl,
		InvalidRecordDecl,
		InvalidEnumDecl,
		InvalidStatement,
		MultiLineString,

		// Semantic errors
		IdentifierInUse,
		IdentifierUseBeforeDecl,
		InvalidExitContinue
	};
}

#endif

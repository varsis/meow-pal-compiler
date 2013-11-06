#ifndef ERRORCODES_H
#define ERRORCODES_H

namespace Meow
{
	enum ErrorCode
	{
		// Syntax errors
		OtherError = 1,
		SyntaxError = 2,
		UnclosedComment = 3,
		UnclosedString = 4,
		InvalidString = 5,
		UnrecognizedSymbol = 6,
		InvalidIdentifier = 7,
		NestedComment = 8,
		UnmatchedComment = 9,
		MissingProgramParentheses = 10,
		MissingProgramPeriod = 11,
		CStyleAssignment = 12,
		MismatchedBlock = 13,
		InvalidExpression = 14,
		InvalidProgramHeader = 15,
		InvalidConstDecl = 16,
		InvalidTypeDecl = 17,
		InvalidVarDecl = 18,
		InvalidFunctDecl = 19,
		InvalidProcDecl = 20,
		InvalidUpTo = 21,
		InvalidArrayDecl = 22,
		InvalidRecordDecl = 23,
		InvalidEnumDecl = 24,
		InvalidStatement = 25,
		MultiLineString = 26,

		// Semantic errors
		SemanticError = 27,
		IdentifierInUse = 28,
		OperatorTypeMismatch = 29,
		IdentifierUseBeforeDecl = 30,
		InvalidExitContinue = 31
	};
}

#endif

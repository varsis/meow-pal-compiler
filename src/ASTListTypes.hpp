#ifndef ASTLISTTYPES_HPP
#define ASTLISTTYPES_HPP

#include <vector>

namespace Meow
{

	class Expression;
	class Statement;
	class ConstantDeclaration;
	class TypeDeclaration;
	class VariableDeclaration;
	class ProcedureDeclaration;
	class Identifier;
	class Field;

	typedef std::vector<Expression*> ExpressionList;
	typedef std::vector<Identifier*> IdentifierList;
	typedef std::vector<Field*> FieldList;
	typedef std::vector<Statement*> StatementList;
	typedef std::vector<ConstantDeclaration*> ConstantDeclarationList;
	typedef std::vector<TypeDeclaration*> TypeDeclarationList;
	typedef std::vector<VariableDeclaration*> VariableDeclarationList;
	typedef std::vector<ProcedureDeclaration*> ProcedureDeclarationList;

}
#endif

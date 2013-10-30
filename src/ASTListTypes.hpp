#ifndef ASTLISTTYPES_HPP
#define ASTLISTTYPES_HPP

#include <vector>

typedef vector<Expression*> ExpressionList;
typedef vector<Statement*> StatementList;
typedef vector<ConstantDeclaration*> ConstantDeclarationList;
typedef vector<TypeDeclaration*> TypeDeclarationList;
typedef vector<VariableDeclaration*> VariableDeclarationList;
typedef vector<ProcedureDeclaration*> ProcedureDeclarationList;

#endif
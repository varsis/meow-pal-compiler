#ifndef VISITOR_HPP
#define VISITOR_HPP

namespace Meow
{

	class ASTNode;
	class ASTListTypes;
	class Program;
	class Declarations;
	class ConstantDeclaration;
	class VariableDeclaration;
	class TypeDeclaration;
	class Type;
	class SimpleType;
	class EnumeratedType;
	class ArrayType;
	class ArrayTypeIndex;
	class ArrayRangeIndex;
	class RecordType;
	class Field;
	class ProcedureDeclaration;
	class ProcedureHeading;
	class ParameterList;
	class Parameter;
	class Identifier;
	class StringLiteral;
	class Constant;
	class IntegerConstant;
	class RealConstant;
	class LValue;
	class Expression;
	class ConstantExpression;
	class SimpleExpression;
	class CompoundStatement;
	class AssignStatement;
	class ConditionalStatement;
	class WhileStatement;
	class ContinueStatement;
	class ExitStatement;
	class RecordField;
	class Variable;
	class SubscriptedVariable;
	class ProcedureInvocation;
	class FunctionInvocation;
	class Arguments;
	class EqualExpression;
	class NotEqualExpression;
	class LessThanEqualExpression;
	class LessThanExpression;
	class GreaterThanEqualExpression;
	class GreaterThanExpression;
	class UnaryPlusExpression;
	class UnaryMinusExpression;
	class AddExpression;
	class SubtractExpression;
	class OrExpression;
	class MultiplyExpression;
	class RealDivideExpression;
	class IntDivideExpression;
	class ModExpression;
	class AndExpression;
	class NotExpression;

	class Visitor
	{
		public:

			virtual void pushNode(const ASTNode* prog);
			virtual void popNode(const ASTNode* prog);

			virtual void visit(const ASTNode* prog) = 0;
			virtual void visit(const Program* prog) = 0;

			virtual void visit(const Declarations* decls) = 0;
			virtual void visit(const ConstantDeclaration* constantDecl) = 0;
			virtual void visit(const TypeDeclaration* typeDecl) = 0;
			virtual void visit(const VariableDeclaration* varDecl) = 0;
			virtual void visit(const ProcedureDeclaration* procDecl) = 0;

			virtual void visit(const Type*) = 0;
			virtual void visit(const SimpleType*) = 0;
			virtual void visit(const EnumeratedType*) = 0;
			virtual void visit(const ArrayType*) = 0;
			virtual void visit(const ArrayTypeIndex*) = 0;
			virtual void visit(const ArrayRangeIndex*) = 0;
			virtual void visit(const RecordType*) = 0;
			virtual void visit(const Field*) = 0;
			virtual void visit(const ProcedureHeading*) = 0;
			virtual void visit(const ParameterList*) = 0;
			virtual void visit(const Parameter*) = 0;
			virtual void visit(const Identifier*) = 0;
			virtual void visit(const StringLiteral*) = 0;
			virtual void visit(const Constant*) = 0;
			virtual void visit(const RealConstant*) = 0;
			virtual void visit(const IntegerConstant*) = 0;
			virtual void visit(const LValue*) = 0;

			virtual void visit(const Expression*) = 0;
			virtual void visit(const ConstantExpression*) = 0;
			virtual void visit(const SimpleExpression*) = 0;
			virtual void visit(const CompoundStatement*) = 0;
			virtual void visit(const AssignStatement*) = 0;
			virtual void visit(const ConditionalStatement*) = 0;
			virtual void visit(const WhileStatement*) = 0;
			virtual void visit(const ContinueStatement*) = 0;
			virtual void visit(const ExitStatement*) = 0;

			virtual void visit(const RecordField*) = 0;
			virtual void visit(const Variable*) = 0;
			virtual void visit(const SubscriptedVariable*) = 0;

			virtual void visit(const ProcedureInvocation*) = 0;
			virtual void visit(const FunctionInvocation*) = 0;
			virtual void visit(const Arguments*) = 0;

			virtual void visit(const EqualExpression*) = 0;
			virtual void visit(const NotEqualExpression*) = 0;
			virtual void visit(const LessThanEqualExpression*) = 0;
			virtual void visit(const LessThanExpression*) = 0;
			virtual void visit(const GreaterThanEqualExpression*) = 0;
			virtual void visit(const GreaterThanExpression*) = 0;

			virtual void visit(const UnaryPlusExpression*) = 0;
			virtual void visit(const UnaryMinusExpression*) = 0;

			virtual void visit(const AddExpression*) = 0;
			virtual void visit(const SubtractExpression*) = 0;
			virtual void visit(const OrExpression*) = 0;
			virtual void visit(const MultiplyExpression*) = 0;
			virtual void visit(const RealDivideExpression*) = 0;
			virtual void visit(const IntDivideExpression*) = 0;
			virtual void visit(const ModExpression*) = 0;
			virtual void visit(const AndExpression*) = 0;
			virtual void visit(const NotExpression*) = 0;

			// Add more as we add more node types

		protected:
			unsigned int m_treeLevel;
	};
}

#endif

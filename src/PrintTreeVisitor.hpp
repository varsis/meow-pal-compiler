#ifndef PRINTTREEVISITOR_HPP
#define PRINTTREEVISITOR_HPP

#include "Visitor.hpp"

namespace Meow
{
	class PrintTreeVisitor : public Visitor
	{
		public:

			PrintTreeVisitor();

			virtual void visit(const ASTNode* node);
			virtual void visit(const Program* prog);
			virtual void visit(const Declarations* decls);
			virtual void visit(const ConstantDeclaration* constantDecl);
			virtual void visit(const TypeDeclaration* typeDecl);
			virtual void visit(const VariableDeclaration* varDecl);
			virtual void visit(const ProcedureDeclaration* procDecl);
			virtual void visit(const Type*);
			virtual void visit(const SimpleType*);
			virtual void visit(const EnumeratedType*);
			virtual void visit(const ArrayType*);
			virtual void visit(const ArrayTypeIndex*);
			virtual void visit(const ArrayRangeIndex*);
			virtual void visit(const RecordType*);
			virtual void visit(const Field*);
			virtual void visit(const ProcedureHeading*);
			virtual void visit(const ParameterList*);
			virtual void visit(const Parameter*);
			virtual void visit(const Identifier*);
			virtual void visit(const StringLiteral*);
			virtual void visit(const Constant*);
			virtual void visit(const RealConstant*);
			virtual void visit(const IntegerConstant*);
			virtual void visit(const LValue*);
			virtual void visit(const Expression*);
			virtual void visit(const ConstantExpression*);
			virtual void visit(const SimpleExpression*);
			virtual void visit(const CompoundStatement*);
			virtual void visit(const AssignStatement*);
			virtual void visit(const ConditionalStatement*);
			virtual void visit(const WhileStatement*);
			virtual void visit(const ContinueStatement*);
			virtual void visit(const ExitStatement*);
			virtual void visit(const RecordField*);
			virtual void visit(const Variable*);
			virtual void visit(const SubscriptedVariable*);
			virtual void visit(const ProcedureInvocation*);
			virtual void visit(const FunctionInvocation*);
			virtual void visit(const Arguments*);
			virtual void visit(const EqualExpression*);
			virtual void visit(const NotEqualExpression*);
			virtual void visit(const LessThanEqualExpression*);
			virtual void visit(const LessThanExpression*);
			virtual void visit(const GreaterThanEqualExpression*);
			virtual void visit(const GreaterThanExpression*);
			virtual void visit(const UnaryPlusExpression*);
			virtual void visit(const UnaryMinusExpression*);
			virtual void visit(const AddExpression*);
			virtual void visit(const SubtractExpression*);
			virtual void visit(const OrExpression*);
			virtual void visit(const MultiplyExpression*);
			virtual void visit(const RealDivideExpression*);
			virtual void visit(const IntDivideExpression*);
			virtual void visit(const ModExpression*);
			virtual void visit(const AndExpression*);
			virtual void visit(const NotExpression*);

		private:
			void addIndent();

	};
}
#endif

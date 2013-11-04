#include <iostream>
#include "PrintTreeVisitor.hpp"

using namespace std;

namespace Meow
{

	PrintTreeVisitor::PrintTreeVisitor()
	{
	}

	// Indents according to the depth of the node in the tree
	void PrintTreeVisitor::addIndent()
	{
		for (unsigned int i = 0; i < m_level; ++i)
		{
			cout << "  ";
		}
	}

	void PrintTreeVisitor::visit(const ASTNode* prog)
	{
		addIndent();
		cout << "AST NODE" << endl;
	}

	void PrintTreeVisitor::visit(const Program* prog)
	{
		addIndent();
		cout << "PROGRAM" << endl;
	}

	void PrintTreeVisitor::visit(const Declarations* decls)
	{
		addIndent();
		cout << "DECLARATIONS" << endl;
	}

	void PrintTreeVisitor::visit(const ConstantDeclaration* constantDecl)
	{
		addIndent();
		cout << "CONSTANT DECLARATION" << endl;
	}

	void PrintTreeVisitor::visit(const TypeDeclaration* typeDecl)
	{
		addIndent();
		cout << "TYPE DECLARATION" << endl;
	}

	void PrintTreeVisitor::visit(const VariableDeclaration* varDecl)
	{
		addIndent();
		cout << "VARIABLE DECLARATION" << endl;
	}

	void PrintTreeVisitor::visit(const ProcedureDeclaration* procDecl)
	{
		addIndent();
		cout << "PROCEDURE DECLARATION" << endl;
	}

	void PrintTreeVisitor::visit(const Type*)
	{
		addIndent();
		cout << "TYPE" << endl;
	}

	void PrintTreeVisitor::visit(const SimpleType*)
	{
		addIndent();
		cout << "SIMPLE TYPE" << endl;
	}

	void PrintTreeVisitor::visit(const EnumeratedType*)
	{
		addIndent();
		cout << "ENUMERATED TYPE" << endl;
	}
	
	void PrintTreeVisitor::visit(const ArrayType*)
	{
		addIndent();
		cout << "ARRAY TYPE" << endl;
	}

	void PrintTreeVisitor::visit(const ArrayTypeIndex*)
	{
		addIndent();
		cout << "ARRAY TYPE INDEX" << endl;
	}

	void PrintTreeVisitor::visit(const ArrayRangeIndex*)
	{
		addIndent();
		cout << "ARRAY RANGE INDEX" << endl;
	}

	void PrintTreeVisitor::visit(const RecordType*)
	{
		addIndent();
		cout << "RECORD TYPE" << endl;
	}

	void PrintTreeVisitor::visit(const Field*)
	{
		addIndent();
		cout << "FIELD" << endl;
	}

	void PrintTreeVisitor::visit(const ProcedureHeading*)
	{
		addIndent();
		cout << "PROCEDURE HEADING" << endl;
	}

	void PrintTreeVisitor::visit(const ParameterList*)
	{
		addIndent();
		cout << "PARAMETER LIST" << endl;
	}

	void PrintTreeVisitor::visit(const Parameter*)
	{
		addIndent();
		cout << "PARAMETER" << endl;
	}

	void PrintTreeVisitor::visit(const Identifier*)
	{
		addIndent();
		cout << "IDENTIFIER" << endl;
	}

	void PrintTreeVisitor::visit(const StringLiteral*)
	{
		addIndent();
		cout << "STRING LITERAL" << endl;
	}

	void PrintTreeVisitor::visit(const Constant*)
	{
	}

	void PrintTreeVisitor::visit(const RealConstant*)
	{
	}

	void PrintTreeVisitor::visit(const IntegerConstant*)
	{
	}

	void PrintTreeVisitor::visit(const LValue*)
	{
	}

	void PrintTreeVisitor::visit(const Expression*)
	{
	}

	void PrintTreeVisitor::visit(const ConstantExpression*)
	{
	}

	void PrintTreeVisitor::visit(const SimpleExpression*)
	{
	}

	void PrintTreeVisitor::visit(const CompoundStatement*)
	{
	}
	
	void PrintTreeVisitor::visit(const AssignStatement*)
	{
	}

	void PrintTreeVisitor::visit(const ConditionalStatement*)
	{
	}

	void PrintTreeVisitor::visit(const WhileStatement*)
	{
	}

	void PrintTreeVisitor::visit(const ContinueStatement*)
	{
	}

	void PrintTreeVisitor::visit(const ExitStatement*)
	{
	}

	void PrintTreeVisitor::visit(const RecordField*)
	{
	}

	void PrintTreeVisitor::visit(const Variable*)
	{
	}

	void PrintTreeVisitor::visit(const SubscriptedVariable*)
	{
	}

	void PrintTreeVisitor::visit(const ProcedureInvocation*)
	{
	}

	void PrintTreeVisitor::visit(const FunctionInvocation*)
	{
	}

	void PrintTreeVisitor::visit(const Arguments*)
	{
	}

	void PrintTreeVisitor::visit(const EqualExpression*)
	{
	}

	void PrintTreeVisitor::visit(const NotEqualExpression*)
	{
	}

	void PrintTreeVisitor::visit(const LessThanEqualExpression*)
	{
	}

	void PrintTreeVisitor::visit(const LessThanExpression*)
	{
	}

	void PrintTreeVisitor::visit(const GreaterThanEqualExpression*)
	{
	}

	void PrintTreeVisitor::visit(const GreaterThanExpression*)
	{
	}

	void PrintTreeVisitor::visit(const UnaryPlusExpression*)
	{
	}

	void PrintTreeVisitor::visit(const UnaryMinusExpression*)
	{
	}

	void PrintTreeVisitor::visit(const AddExpression*)
	{
	}

	void PrintTreeVisitor::visit(const SubtractExpression*)
	{
	}

	void PrintTreeVisitor::visit(const OrExpression*)
	{
	}

	void PrintTreeVisitor::visit(const MultiplyExpression*)
	{
	}

	void PrintTreeVisitor::visit(const RealDivideExpression*)
	{
	}

	void PrintTreeVisitor::visit(const IntDivideExpression*)
	{
	}

	void PrintTreeVisitor::visit(const ModExpression*)
	{
	}

	void PrintTreeVisitor::visit(const AndExpression*)
	{
	}

	void PrintTreeVisitor::visit(const NotExpression*)
	{
	}
}

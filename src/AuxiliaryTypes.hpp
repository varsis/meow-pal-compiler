#ifndef AUXTYPES_HPP
#define AUXTYPES_HPP

#include <string>
#include <vector>

namespace Meow
{
	class Type;

	struct ArrayIndexRange
	{
		int start;
		int end;
	};

	union Value
	{
		int int_val;
		double real_val;
	};

	struct FieldDecl
	{
		Meow::Type* type;
		std::vector<std::string*>* fieldNames;
	};

	struct LValue
	{
		Meow::Type* type;
		bool assignable;
	};

	// Will need to switch this once we start doing code gen
	typedef std::vector<LValue> InvocationParameters;
	
	struct ProcedureInvocation
	{
		InvocationParameters* params;
		std::string* procedureName;
	};

	enum ProcedureClass
	{
		UserDefined,
		BuiltInInput,
		BuiltInOutput
	};

	// For procedure/function params as well as record fields
	typedef std::pair<std::string*, Meow::Type*> IdTypePair;
	typedef std::vector<IdTypePair*> IdTypePairList;
	
	struct Parameter
	{
		std::string id;
		Type* type;
		bool var;
	};

	typedef std::vector<Parameter> ParameterList;
}
#endif

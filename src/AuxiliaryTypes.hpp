#ifndef AUXTYPES_HPP
#define AUXTYPES_HPP

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

	// For procedure/function params as well as record fields
	typedef std::pair<std::string*, Meow::Type*> IdTypePair;
	typedef std::vector<IdTypePair*> IdTypePairList;
}
#endif

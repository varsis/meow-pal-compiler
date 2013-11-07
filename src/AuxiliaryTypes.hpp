#ifndef AUXTYPES_HPP
#define AUXTYPES_HPP
namespace Meow
{
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
}
#endif

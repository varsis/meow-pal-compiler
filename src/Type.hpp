#ifndef TYPE_HPP
#define TYPE_HPP

namespace Meow
{
	class Type
	{
		public:

			Type(bool primitive = false)
				: m_primitiveType(primitive)
			{
			}

			bool m_primitiveType;
	};
}

#endif

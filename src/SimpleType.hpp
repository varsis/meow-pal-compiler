#ifndef SIMPLETYPE_HPP
#define SIMPLETYPE_HPP

#include "Type.hpp"

// Forward Declarations
namespace Meow
{
	class Visitor;
	class TypeVisitor;
	class Identifier;

	class SimpleType : public Type
	{
		public:
			SimpleType(Identifier* name);

			virtual void accept(Visitor* visitor);
			virtual Type* accept(TypeVisitor* visitor);

		private:
			Identifier* m_name;
	};
}

#endif

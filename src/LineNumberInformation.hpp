#ifndef LINENUMBERINFORMATION_HPP
#define LINENUMBERINFORMATION_HPP

namespace Meow
{
	class LineNumberInformation {
		public:
			LineNumberInformation();
			unsigned int get_lineNumber() const;
			void set_lineNumber(unsigned int lineNumber);
		private:
			unsigned int lineNumber;
	};
}

#endif

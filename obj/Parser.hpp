#pragma once

namespace Meow {
	class Parser {
		public:
			Parser() : parser(scanner) {}
		
			int parse() {
				return parser.parse();
			}
		
		private:
			FlexScanner scanner;
			BisonParser parser;
	};
}

#pragma once

namespace Meow {
	class Parser {
		public:
			Parser() : parser(scanner) {}
		
			int parse() {
				return parser.parse();
			}
		
		private:
			PalScanner scanner;
			PalParser parser;
	};
}

%{
	#include "logic_calculator_scanner.hpp"
	typedef LogicCalculator::BisonParser::token token;
%}

%option nodefault yyclass="FlexScanner" noyywrap c++


%%
"[ \t\n]" { ; /* Ignore whitespace */ }
"//((\w| )*)" { ; /* Ignore single line comments */ }
\{ { return token::LEFT_BRACE; }
\} { return token::RIGHT_BRACE; }
\[ { return token::LEFT_BRACKET; }
\] { return token::RIGHT_BRACKET; }
\( { return token::LEFT_PAREN; }
\) { return token::RIGHT_PAREN; }
\' { return token::QUOTE; }
; { return token::SEMICOLON; }


:= { return token::ASSIGN; }
<= { return token::LE; }
>= { return token::GE; }
<> { return token::NE; }
= { return token::EQ; }
< { return token::LT; }
> { return token::GT; }
\+ { return token::ADD; }
\- { return token::SUBTRACT; }
\* { return token::MULTIPLY; }
\/ { return token::REAL_DIVIDE; }

: { return token::COLON; }

and { return token::AND; }
array { return token::ARRAY; }
begin { return token::BEGIN; }
bool { return token::BOOL; }
char { return token::CHAR; }
const { return token::CONST; }
continue { return token::CONTINUE; }
div { return token::DIV; }
do { return token::DO; }
else { return token::ELSE; }
end { return token::END; }
exit { return token::EXIT; }
function { return token::FUNCTION; }
if { return token::IF; }
mod { return token::MOD; }
not { return token::NOT; }
of { return token::OF; }
or { return token::OR; }
procedure { return token::PROCEDURE; }
program { return token::PROGRAM; }
record { return token::RECORD; }
then { return token::THEN; }
type { return token::TYPE; }
var { return token::VAR; }
while { return token::WHILE; }
div { return token::INT_DIVIDE; }
mod { return token::MOD; }

"'([a-zA-Z0-9]|\\n|\\t| |(\\){2})*" { return token::BEGIN_STRING; }
([a-zA-A]+[0-9]*) { return token::IDENTIFIER; }

. { std::cerr << "** " << "(" << yylineno << ") lex: Unknown symbol \'" << yytext[0] << "\'\n"; }



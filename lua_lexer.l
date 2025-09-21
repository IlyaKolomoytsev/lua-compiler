%option never-interactive

%{
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <iostream>

using std::cout;
using std::endl;
%}

%x COMMENT STRING

%%

"and"           { cout << "Keyword: " << yytext << '\n'; }
"break"         { cout << "Keyword: " << yytext << '\n'; }
"do"            { cout << "Keyword: " << yytext << '\n'; }
"elseif"        { cout << "Keyword: " << yytext << '\n'; }
"else"          { cout << "Keyword: " << yytext << '\n'; }
"end"           { cout << "Keyword: " << yytext << '\n'; }
"for"           { cout << "Keyword: " << yytext << '\n'; }
"function"      { cout << "Keyword: " << yytext << '\n'; }
"goto"          { cout << "Keyword: " << yytext << '\n'; }
"if"            { cout << "Keyword: " << yytext << '\n'; }
"in"            { cout << "Keyword: " << yytext << '\n'; }
"local"         { cout << "Keyword: " << yytext << '\n'; }
"nil"           { cout << "Keyword: " << yytext << '\n'; }
"not"           { cout << "Keyword: " << yytext << '\n'; }
"or"            { cout << "Keyword: " << yytext << '\n'; }
"repeat"        { cout << "Keyword: " << yytext << '\n'; }
"return"        { cout << "Keyword: " << yytext << '\n'; }
"then"          { cout << "Keyword: " << yytext << '\n'; }
"until"         { cout << "Keyword: " << yytext << '\n'; }
"while"         { cout << "Keyword: " << yytext << '\n'; }

"true"          { cout << "Boolean: " << yytext << '\n'; }
"false"         { cout << "Boolean: " << yytext << '\n'; }

"__add"         { cout << "Metamethod: " << yytext << " (operator +)\n"; }
"__sub"         { cout << "Metamethod: " << yytext << " (operator -)\n"; }
"__mul"         { cout << "Metamethod: " << yytext << " (operator *)\n"; }
"__div"         { cout << "Metamethod: " << yytext << " (operator /)\n"; }
"__mod"         { cout << "Metamethod: " << yytext << " (operator %)\n"; }
"__pow"         { cout << "Metamethod: " << yytext << " (operator ^)\n"; }
"__unm"         { cout << "Metamethod: " << yytext << " (operator -)\n"; }
"__idiv"        { cout << "Metamethod: " << yytext << " (operator //)\n"; }
"__band"        { cout << "Metamethod: " << yytext << " (operator &)\n"; }
"__bor"         { cout << "Metamethod: " << yytext << " (operator |)\n"; }
"__bxor"        { cout << "Metamethod: " << yytext << " (operator ~)\n"; }
"__bnot"        { cout << "Metamethod: " << yytext << " (operator ~)\n"; }
"__shl"         { cout << "Metamethod: " << yytext << " (operator <<)\n"; }
"__shr"         { cout << "Metamethod: " << yytext << " (operator >>)\n"; }
"__concat"      { cout << "Metamethod: " << yytext << " (operator ..)\n"; }
"__len"         { cout << "Metamethod: " << yytext << " (operator #)\n"; }
"__eq"          { cout << "Metamethod: " << yytext << " (operator ==)\n"; }
"__lt"          { cout << "Metamethod: " << yytext << " (operator <)\n"; }
"__le"          { cout << "Metamethod: " << yytext << " (operator <=)\n"; }
"__index"       { cout << "Metamethod: " << yytext << " (table[key])\n"; }
"__newindex"    { cout << "Metamethod: " << yytext << " (table[key] = value)\n"; }
"__call"        { cout << "Metamethod: " << yytext << " (func(args))\n"; }

"..."           { cout << "Varargs: " << yytext << '\n'; }
"::"            { cout << "LabelSep: " << yytext << '\n'; }
"//"            { cout << "Operator: " << yytext << " (int div)\n"; }
".."            { cout << "Operator: " << yytext << " (concat)\n"; }
"=="            { cout << "Operator: " << yytext << '\n'; }
"~="            { cout << "Operator: " << yytext << '\n'; }
"<="            { cout << "Operator: " << yytext << '\n'; }
">="            { cout << "Operator: " << yytext << '\n'; }
"<<"            { cout << "Operator: " << yytext << " (shl)\n"; }
">>"            { cout << "Operator: " << yytext << " (shr)\n"; }

"+"             { cout << "Operator: " << yytext << '\n'; }
"-"             { cout << "Operator: " << yytext << '\n'; }
"*"             { cout << "Operator: " << yytext << '\n'; }
"/"             { cout << "Operator: " << yytext << '\n'; }
"%"             { cout << "Operator: " << yytext << '\n'; }
"^"             { cout << "Operator: " << yytext << '\n'; }
"#"             { cout << "Operator: " << yytext << " (len)\n"; }

"&"             { cout << "Operator: " << yytext << " (band)\n"; }
"|"             { cout << "Operator: " << yytext << " (bor)\n"; }
"~"             { cout << "Operator: " << yytext << " (bxor / bnot)\n"; }

"="             { cout << "Assign: "  << yytext << '\n'; }
"<"             { cout << "Operator: " << yytext << '\n'; }
">"             { cout << "Operator: " << yytext << '\n'; }
"."             { cout << "Dot: "     << yytext << '\n'; }
":"             { cout << "Colon: "   << yytext << '\n'; }
","             { cout << "Comma: "   << yytext << '\n'; }
";"             { cout << "Semicolon: " << yytext << '\n'; }

"("             { cout << "LParen: "  << yytext << '\n'; }
")"             { cout << "RParen: "  << yytext << '\n'; }
"["             { cout << "LBracket: "<< yytext << '\n'; }
"]"             { cout << "RBracket: "<< yytext << '\n'; }
"{"             { cout << "LBrace: "  << yytext << '\n'; }
"}"             { cout << "RBrace: "  << yytext << '\n'; }

%%



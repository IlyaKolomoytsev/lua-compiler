%option never-interactive

%x LCOMM // состояние многострочного комментария

/* Макросы */
ID_START                [A-Za-z_]
ID_CONT                 [A-Za-z0-9_]*
WS                      [ \t\r\n\v\f]+

DIGIT                   [0-9]

DEC_INT                 {DIGIT}+
DEC_EXP                 [eE][+-]?{DIGIT}+
DEC_FLOAT               ( ({DIGIT}+"."{DIGIT}* | "."{DIGIT}+){DEC_EXP}? | {DIGIT}+{DEC_EXP} )

HEX_DIGIT               [0-9A-Fa-f]
HEX_PREFIX              0[xX]
HEX_EXP                 [pP][+-]?{DIGIT}+
HEX_INT                 {HEX_PREFIX}{HEX_DIGIT}+
HEX_FLOAT               {HEX_PREFIX}({HEX_DIGIT}+"."{HEX_DIGIT}* | "."{HEX_DIGIT}+){HEX_EXP}


%{
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <iostream>

using std::cout;

static char comment_buf[8192];
static size_t comment_pos = 0;

static inline void append_to_comments(const char* s, size_t n) {
    if (comment_pos + n >= sizeof(comment_buf)) n = sizeof(comment_buf) - 1 - comment_pos;
    if (n > 0) {
        std::memcpy(comment_buf + comment_pos, s, n);
        comment_pos += n;
        comment_buf[comment_pos] = '\0';
    }
}

%}


%%

/* Ключевые слова */
"and"                   { cout << "Keyword: " << yytext << '\n'; }
"break"                 { cout << "Keyword: " << yytext << '\n'; }
"do"                    { cout << "Keyword: " << yytext << '\n'; }
"elseif"                { cout << "Keyword: " << yytext << '\n'; }
"else"                  { cout << "Keyword: " << yytext << '\n'; }
"end"                   { cout << "Keyword: " << yytext << '\n'; }
"for"                   { cout << "Keyword: " << yytext << '\n'; }
"function"              { cout << "Keyword: " << yytext << '\n'; }
"goto"                  { cout << "Keyword: " << yytext << '\n'; }
"if"                    { cout << "Keyword: " << yytext << '\n'; }
"in"                    { cout << "Keyword: " << yytext << '\n'; }
"local"                 { cout << "Keyword: " << yytext << '\n'; }
"nil"                   { cout << "Keyword: " << yytext << '\n'; }
"not"                   { cout << "Keyword: " << yytext << '\n'; }
"or"                    { cout << "Keyword: " << yytext << '\n'; }
"repeat"                { cout << "Keyword: " << yytext << '\n'; }
"return"                { cout << "Keyword: " << yytext << '\n'; }
"then"                  { cout << "Keyword: " << yytext << '\n'; }
"until"                 { cout << "Keyword: " << yytext << '\n'; }
"while"                 { cout << "Keyword: " << yytext << '\n'; }

"true"                  { cout << "Boolean: " << yytext << '\n'; }
"false"                 { cout << "Boolean: " << yytext << '\n'; }

/* Метаметоды */
"__add"                 { cout << "Metamethod: " << yytext << " (operator +)\n"; }
"__sub"                 { cout << "Metamethod: " << yytext << " (operator -)\n"; }
"__mul"                 { cout << "Metamethod: " << yytext << " (operator *)\n"; }
"__div"                 { cout << "Metamethod: " << yytext << " (operator /)\n"; }
"__mod"                 { cout << "Metamethod: " << yytext << " (operator %)\n"; }
"__pow"                 { cout << "Metamethod: " << yytext << " (operator ^)\n"; }
"__unm"                 { cout << "Metamethod: " << yytext << " (operator -)\n"; }
"__idiv"                { cout << "Metamethod: " << yytext << " (operator //)\n"; }
"__band"                { cout << "Metamethod: " << yytext << " (operator &)\n"; }
"__bor"                 { cout << "Metamethod: " << yytext << " (operator |)\n"; }
"__bxor"                { cout << "Metamethod: " << yytext << " (operator ~)\n"; }
"__bnot"                { cout << "Metamethod: " << yytext << " (operator ~)\n"; }
"__shl"                 { cout << "Metamethod: " << yytext << " (operator <<)\n"; }
"__shr"                 { cout << "Metamethod: " << yytext << " (operator >>)\n"; }
"__concat"              { cout << "Metamethod: " << yytext << " (operator ..)\n"; }
"__len"                 { cout << "Metamethod: " << yytext << " (operator #)\n"; }
"__eq"                  { cout << "Metamethod: " << yytext << " (operator ==)\n"; }
"__lt"                  { cout << "Metamethod: " << yytext << " (operator <)\n"; }
"__le"                  { cout << "Metamethod: " << yytext << " (operator <=)\n"; }
"__index"               { cout << "Metamethod: " << yytext << " (table[key])\n"; }
"__newindex"            { cout << "Metamethod: " << yytext << " (table[key] = value)\n"; }
"__call"                { cout << "Metamethod: " << yytext << " (func(args))\n"; }

/* Комментарии */


/* Операторы (многосимвольные) */
"..."                   { cout << "Varargs: " << yytext << '\n'; }
"::"                    { cout << "LabelSep: " << yytext << '\n'; }
"//"                    { cout << "Operator: " << yytext << " (int div)\n"; }
".."                    { cout << "Operator: " << yytext << " (concat)\n"; }
"=="                    { cout << "Operator: " << yytext << '\n'; }
"~="                    { cout << "Operator: " << yytext << '\n'; }
"<="                    { cout << "Operator: " << yytext << '\n'; }
">="                    { cout << "Operator: " << yytext << '\n'; }
"<<"                    { cout << "Operator: " << yytext << " (shl)\n"; }
">>"                    { cout << "Operator: " << yytext << " (shr)\n"; }

/* Операторы (односимвольные) */
"+"                     { cout << "Operator: " << yytext << '\n'; }
"-"                     { cout << "Operator: " << yytext << '\n'; }
"*"                     { cout << "Operator: " << yytext << '\n'; }
"/"                     { cout << "Operator: " << yytext << '\n'; }
"%"                     { cout << "Operator: " << yytext << '\n'; }
"^"                     { cout << "Operator: " << yytext << '\n'; }
"#"                     { cout << "Operator: " << yytext << " (len)\n"; }
"&"                     { cout << "Operator: " << yytext << " (band)\n"; }
"|"                     { cout << "Operator: " << yytext << " (bor)\n"; }
"~"                     { cout << "Operator: " << yytext << " (bxor / bnot)\n"; }
"="                     { cout << "Operator: "  << yytext << '\n'; }
"<"                     { cout << "Operator: " << yytext << '\n'; }
">"                     { cout << "Operator: " << yytext << '\n'; }
"."                     { cout << "Operator: "     << yytext << '\n'; }
":"                     { cout << "Operator: "   << yytext << '\n'; }
","                     { cout << "Operator: "   << yytext << '\n'; }
";"                     { cout << "Operator: " << yytext << '\n'; }

/* Скобки */
"("                     { cout << "LParen: "  << yytext << '\n'; }
")"                     { cout << "RParen: "  << yytext << '\n'; }
"["                     { cout << "LBracket: "<< yytext << '\n'; }
"]"                     { cout << "RBracket: "<< yytext << '\n'; }
"{"                     { cout << "LBrace: "  << yytext << '\n'; }
"}"                     { cout << "RBrace: "  << yytext << '\n'; }

/* Идентификаторы */
{ID_START}{ID_CONT}     { cout << "Identifier: " << yytext << '\n'; }

/* Числовые литералы */
{HEX_FLOAT}             { cout << "Float(hex): " << strtod(yytext, nullptr) << '\n'; }
{HEX_INT}               { cout << "Int(hex): " << strtoll(yytext, nullptr, 0) << '\n'; }
{DEC_FLOAT}             { cout << "Float: " << strtod(yytext, nullptr) << '\n'; }
{DEC_INT}               { cout << "Int: " << strtoll(yytext, nullptr, 10) << '\n'; }


/* Пробельные символы */
{WS}            ;

%%



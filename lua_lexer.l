%option never-interactive
%option yylineno
%option noyywrap

/* состояние однострочного комментария */
%x SCOMM
/* состояние многострочного комментария */
%x MCOMM
/* строки в двойных кавычках */
%x DSTRING
/* строки в одинарных кавычках */
%x SSTRING

/* Макросы */
ID_START                [A-Za-z_]
ID_CONT                 [A-Za-z0-9_]*
WS                      [ \t\r\n\v\f]+

DIGIT                   [0-9]

DEC_INT                 {DIGIT}+
DEC_EXP                 [eE][+-]?{DIGIT}+
DEC_FLOAT               (({DIGIT}+"."{DIGIT}*|"."{DIGIT}+){DEC_EXP}?|{DIGIT}+{DEC_EXP})

HEX_DIGIT               [0-9A-Fa-f]
HEX_PREFIX              0[xX]
HEX_EXP                 [pP][+-]?{DIGIT}+
HEX_INT                 {HEX_PREFIX}{HEX_DIGIT}+
HEX_FLOAT               ({HEX_PREFIX}({HEX_DIGIT}+"."{HEX_DIGIT}*|"."{HEX_DIGIT}+){HEX_EXP}?|({HEX_INT}{HEX_EXP}))


%{
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include "lexer/LexerStringBuilder.h"
#include "lua_parser.tab.h"

using std::cout;

static LexerStringBuilder lexerStringMaster = LexerStringBuilder();

/* Прототипы функций */
static inline int hexval(int c);

/* Переменные для работы с комментариями */
static int comment_start_line = 0;

%}

%%

%{
    // ToDo: объявления я так понял должны быть тут.
    // комментарий создан спустя неделю после консультации
%}

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


"--"                    { lexerStringMaster.clear(); comment_start_line = yylineno; BEGIN(SCOMM); }
"--[["                  { lexerStringMaster.clear(); comment_start_line = yylineno; BEGIN(MCOMM); }


<SCOMM>[^\r\n]*           { cout << "Single comment: " << yytext << '\n'; BEGIN(INITIAL); }

<MCOMM>"]]"             { cout << "Multi comment: " << lexerStringMaster.getString() << '\n'; BEGIN(INITIAL); } /* конец многострочного комментария */
<MCOMM>\r\n             { lexerStringMaster.write("\n", 1); }
<MCOMM>\r               { /* игнорируем одиночный CR */ }
<MCOMM>.                { lexerStringMaster.write(yytext, yyleng); }


<MCOMM><<EOF>>          { cout << "ERROR: unterminated multiline comment (opened at line " << comment_start_line << ")\n"; BEGIN(INITIAL); }


\"                      { lexerStringMaster.clear(); BEGIN(DSTRING); } /* Старт строки с " */
\'                      { lexerStringMaster.clear(); BEGIN(SSTRING); } /* Старт строки с ' */


<DSTRING>[^"\\\n]+      { lexerStringMaster.write(yytext, yyleng); }
<SSTRING>[^'\\\n]+      { lexerStringMaster.write(yytext, yyleng); }


<DSTRING,SSTRING>\\a    { lexerStringMaster.write('\a'); }
<DSTRING,SSTRING>\\b    { lexerStringMaster.write('\b'); }
<DSTRING,SSTRING>\\f    { lexerStringMaster.write('\f'); }
<DSTRING,SSTRING>\\n    { lexerStringMaster.write('\n'); }
<DSTRING,SSTRING>\\r    { lexerStringMaster.write('\r'); }
<DSTRING,SSTRING>\\t    { lexerStringMaster.write('\t'); }
<DSTRING,SSTRING>\\v    { lexerStringMaster.write('\v'); }
<SSTRING,DSTRING>"\\\"" { lexerStringMaster.write('"'); }
<SSTRING,DSTRING>"\\\'" { lexerStringMaster.write('\''); }
<DSTRING,SSTRING>\\\\   { lexerStringMaster.write('\\'); }


<DSTRING,SSTRING>\\x[0-9A-Fa-f]{2} {
    int hi = hexval(yytext[2]);
    int lo = hexval(yytext[3]);
    lexerStringMaster.write((char)((hi << 4) | lo));
}


<DSTRING,SSTRING>\\[0-9]{1,3} {
    int v = std::strtol(yytext + 1, nullptr, 10);
    if (v < 0) v = 0;
    if (v > 255) v = 255;
    lexerStringMaster.write((char)v);
}


<DSTRING,SSTRING>\\u\{[0-9A-Fa-f]+\} {
    unsigned cp = std::strtol(yytext+3, nullptr, 16);
    if (cp > 0x10FFFF) { cp = 0xFFFD; break; }
    lexerStringMaster.writeUnicodeByCode(cp);
}


<DSTRING,SSTRING>\\\n  { lexerStringMaster.write('\n'); }


<DSTRING>\"             { cout << "String: " << lexerStringMaster.getString() << '\n'; BEGIN(INITIAL); }
<SSTRING>\'             { cout << "String: " << lexerStringMaster.getString() << '\n'; BEGIN(INITIAL); }


<DSTRING>\n             { cout << "ERROR: unterminated string (\") at line " << yylineno << '\n'; BEGIN(INITIAL); }
<SSTRING>\n             { cout << "ERROR: unterminated string (') at line " << yylineno << '\n'; BEGIN(INITIAL); }


<DSTRING><<EOF>>        { cout << "ERROR: unterminated string (\") before EOF\n"; BEGIN(INITIAL); }
<SSTRING><<EOF>>        { cout << "ERROR: unterminated string (') before EOF\n"; BEGIN(INITIAL); }

<DSTRING,SSTRING>\\([^0-9abfnrtv\"\'\\xu\n]) {
    cout << "ERROR: invalid escape '" << yytext << "' at line " << yylineno << '\n';
    lexerStringMaster.write(yytext + 1, yyleng - 1);
}


{HEX_FLOAT}             { cout << "Float(hex): " << strtod(yytext, nullptr) << '\n'; }
{HEX_INT}               { cout << "Int(hex): " << strtoll(yytext, nullptr, 0) << '\n'; }
{DEC_FLOAT}             { cout << "Float: " << strtod(yytext, nullptr) << '\n'; }
{DEC_INT}               { cout << "Int: " << strtoll(yytext, nullptr, 10) << '\n'; }

[0-9]+{ID_START}+ { cout << "Error: invalid identifier (starts with digit): " << yytext << " at line " << yylineno << '\n'; }


"..."                   { cout << "Varargs: " << yytext << '\n'; }
"::"                    { cout << "LabelSep: " << yytext << '\n'; }
"//"                    { cout << "Operator: " << yytext << " (int div)\n"; }
".."                    { cout << "Operator: " << yytext << " (concat)\n"; }
"=="                    { cout << "Operator: " << yytext << '\n'; }
"~="                    { cout << "Operator: " << yytext << '\n'; }
"<="                    { cout << "Operator: " << yytext << '\n'; }
">="                    { cout << "Operator: " << yytext << '\n'; }


"+"                     { cout << "Operator: " << yytext << '\n'; }
"-"                     { cout << "Operator: " << yytext << '\n'; }
"*"                     { cout << "Operator: " << yytext << '\n'; }
"/"                     { cout << "Operator: " << yytext << '\n'; }
"%"                     { cout << "Operator: " << yytext << '\n'; }
"^"                     { cout << "Operator: " << yytext << '\n'; }
"#"                     { cout << "Operator: " << yytext << " (len)\n"; }
"="                     { cout << "Operator: " << yytext << '\n'; }
"<"                     { cout << "Operator: " << yytext << '\n'; }
">"                     { cout << "Operator: " << yytext << '\n'; }
"."                     { cout << "Operator: " << yytext << '\n'; }
":"                     { cout << "Operator: " << yytext << '\n'; }
","                     { cout << "Operator: " << yytext << '\n'; }
";"                     { cout << "Operator: " << yytext << '\n'; }


"("                     { cout << "LParen: "  << yytext << '\n'; }
")"                     { cout << "RParen: "  << yytext << '\n'; }
"["                     { cout << "LBracket: "<< yytext << '\n'; }
"]"                     { cout << "RBracket: "<< yytext << '\n'; }
"{"                     { cout << "LBrace: "  << yytext << '\n'; }
"}"                     { cout << "RBrace: "  << yytext << '\n'; }


{ID_START}{ID_CONT}     { cout << "Identifier: " << yytext << '\n'; }


{WS}            ;

<*>. { cout << "Error: unexpected symbol: " << yytext << " at line " << yylineno << '\n'; }

%%


static inline int hexval(int c) {
    if ('0' <= c && c <= '9') return c - '0';
    if ('a' <= c && c <= 'f') return 10 + (c - 'a');
    if ('A' <= c && c <= 'F') return 10 + (c - 'A');
    return -1;
}

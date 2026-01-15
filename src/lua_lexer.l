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


/* Прототипы функций */
static inline int hexval(int c);

%}

%%

%{
    static int comment_start_line = 0;
    static LexerStringBuilder lexerStringMaster = LexerStringBuilder();
%}

"and"                   { cout << "Keyword: " << yytext << '\n'; return AND; }
"break"                 { cout << "Keyword: " << yytext << '\n'; return BREAK; }
"do"                    { cout << "Keyword: " << yytext << '\n'; return DO; }
"elseif"                { cout << "Keyword: " << yytext << '\n'; return ELSEIF; }
"else"                  { cout << "Keyword: " << yytext << '\n'; return ELSE; }
"end"                   { cout << "Keyword: " << yytext << '\n'; return END; }
"for"                   { cout << "Keyword: " << yytext << '\n'; return FOR; }
"function"              { cout << "Keyword: " << yytext << '\n'; return FUNCTION; }
"goto"                  { cout << "Keyword: " << yytext << '\n'; return GOTO; }
"if"                    { cout << "Keyword: " << yytext << '\n'; return IF; }
"in"                    { cout << "Keyword: " << yytext << '\n'; return IN; }
"local"                 { cout << "Keyword: " << yytext << '\n'; return LOCAL; }
"nil"                   { cout << "Keyword: " << yytext << '\n'; return NIL; }
"not"                   { cout << "Keyword: " << yytext << '\n'; return NOT; }
"or"                    { cout << "Keyword: " << yytext << '\n'; return OR; }
"repeat"                { cout << "Keyword: " << yytext << '\n'; return REPEAT; }
"return"                { cout << "Keyword: " << yytext << '\n'; return RETURN; }
"then"                  { cout << "Keyword: " << yytext << '\n'; return THEN; }
"until"                 { cout << "Keyword: " << yytext << '\n'; return UNTIL; }
"while"                 { cout << "Keyword: " << yytext << '\n'; return WHILE; }

"true"                  { cout << "Boolean: " << yytext << '\n'; return TRUE; }
"false"                 { cout << "Boolean: " << yytext << '\n'; return FALSE; }


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


<DSTRING>\"             { std::string s = lexerStringMaster.getString(); cout << "String: " << s << '\n'; yylval.String = new std::string(s); BEGIN(INITIAL);  return STRING; }
<SSTRING>\'             { std::string s = lexerStringMaster.getString(); cout << "String: " << s << '\n'; yylval.String = new std::string(s); BEGIN(INITIAL);  return STRING; }


<DSTRING>\n             { cout << "ERROR: unterminated string (\") at line " << yylineno << '\n'; BEGIN(INITIAL); }
<SSTRING>\n             { cout << "ERROR: unterminated string (') at line " << yylineno << '\n'; BEGIN(INITIAL); }


<DSTRING><<EOF>>        { cout << "ERROR: unterminated string (\") before EOF\n"; BEGIN(INITIAL); }
<SSTRING><<EOF>>        { cout << "ERROR: unterminated string (') before EOF\n"; BEGIN(INITIAL); }

<DSTRING,SSTRING>\\([^0-9abfnrtv\"\'\\xu\n]) {
    cout << "ERROR: invalid escape '" << yytext << "' at line " << yylineno << '\n';
    lexerStringMaster.write(yytext + 1, yyleng - 1);
}


{HEX_FLOAT}             { cout << "Float(hex): " << strtod(yytext, nullptr) << '\n'; yylval.Float = strtod(yytext, nullptr);  return FLOAT; }
{HEX_INT}               { cout << "Int(hex): " << strtoll(yytext, nullptr, 0) << '\n'; yylval.Int = strtoll(yytext, nullptr, 0); return INT; }
{DEC_FLOAT}             { cout << "Float: " << strtod(yytext, nullptr) << '\n'; yylval.Float = strtod(yytext, nullptr); return FLOAT; }
{DEC_INT}               { cout << "Int: " << strtoll(yytext, nullptr, 10) << '\n'; yylval.Int = strtoll(yytext, nullptr, 10); return INT; }

[0-9]+{ID_START}+ { cout << "Error: invalid identifier (starts with digit): " << yytext << " at line " << yylineno << '\n'; }


"..."                   { cout << "Varargs: " << yytext << '\n'; return VARARG; }
"::"                    { cout << "LabelSep: " << yytext << '\n'; return LABEL_SEP; }
"//"                    { cout << "Operator: " << yytext << " (int div)\n"; return INT_DIV;}
".."                    { cout << "Operator: " << yytext << " (concat)\n"; return CONC; }
"=="                    { cout << "Operator: " << yytext << '\n'; return EQUALITY; }
"~="                    { cout << "Operator: " << yytext << '\n'; return INEQUALITY; }
"<="                    { cout << "Operator: " << yytext << '\n'; return LESS_EQUAL; }
">="                    { cout << "Operator: " << yytext << '\n'; return GREATER_EQUAL; }


"+"                     { cout << "Operator: " << yytext << '\n'; return '+'; }
"-"                     { cout << "Operator: " << yytext << '\n'; return '-'; }
"*"                     { cout << "Operator: " << yytext << '\n'; return '*'; }
"/"                     { cout << "Operator: " << yytext << '\n'; return '/'; }
"%"                     { cout << "Operator: " << yytext << '\n'; return '%'; }
"^"                     { cout << "Operator: " << yytext << '\n'; return '^'; }
"#"                     { cout << "Operator: " << yytext << " (len)\n"; return '#'; }
"="                     { cout << "Operator: " << yytext << '\n'; return '='; }
"<"                     { cout << "Operator: " << yytext << '\n'; return '<'; }
">"                     { cout << "Operator: " << yytext << '\n'; return '>'; }
"."                     { cout << "Operator: " << yytext << '\n'; return '.'; }
":"                     { cout << "Operator: " << yytext << '\n'; return ':'; }
","                     { cout << "Operator: " << yytext << '\n'; return ','; }
";"                     { cout << "Operator: " << yytext << '\n'; return ';'; }


"("                     { cout << "LParen: "  << yytext << '\n'; return '('; }
")"                     { cout << "RParen: "  << yytext << '\n'; return ')'; }
"["                     { cout << "LBracket: "<< yytext << '\n'; return '['; }
"]"                     { cout << "RBracket: "<< yytext << '\n'; return ']'; }
"{"                     { cout << "LBrace: "  << yytext << '\n'; return '{'; }
"}"                     { cout << "RBrace: "  << yytext << '\n'; return '}'; }


{ID_START}{ID_CONT}     { cout << "Identifier: " << yytext << '\n'; yylval.String = new std::string(yytext, yyleng); return ID; }


{WS}            ;

<*>. { cout << "Error: unexpected symbol: " << yytext << " at line " << yylineno << '\n'; }

%%


static inline int hexval(int c) {
    if ('0' <= c && c <= '9') return c - '0';
    if ('a' <= c && c <= 'f') return 10 + (c - 'a');
    if ('A' <= c && c <= 'F') return 10 + (c - 'A');
    return -1;
}

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
HEX_FLOAT               {HEX_PREFIX}({HEX_DIGIT}+"."{HEX_DIGIT}*|"."{HEX_DIGIT}+){HEX_EXP}


%{
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <iostream>

using std::cout;

/* Переменные для работы с комментариями */
static char comment_buf[8192];
static size_t comment_pos = 0;
static int comment_start_line = 0;

/* Переменные для работы со строками */
static size_t string_pos = 0;
static char string_buf[8192]; 

/* Функции для работы с комментариями */
static inline void comm_append(const char* s, size_t n) {
    if (comment_pos + n >= sizeof(comment_buf)) n = sizeof(comment_buf) - 1 - comment_pos;
    if (n > 0) {
        std::memcpy(comment_buf + comment_pos, s, n);
        comment_pos += n;
        comment_buf[comment_pos] = '\0';
    }
}

static inline void comm_reset(){
    comment_pos = 0;
    comment_buf[0] = '\0';
    comment_start_line = 0;
}

/* Функции для работы со строками */
static inline void str_putc(char c) {
    if (string_pos + 1 < sizeof(string_buf)) {
        string_buf[string_pos++] = c;
        string_buf[string_pos] = '\0';
    }
}

static inline void str_append(const char* s, size_t n) {
    if (string_pos + n >= sizeof(string_buf)) n = sizeof(string_buf) - 1 - string_pos;
    if (n > 0) {
        std::memcpy(string_buf + string_pos, s, n);
        string_pos += n;
        string_buf[string_pos] = '\0';
    }
}

static inline int hexval(int c) {
    if ('0' <= c && c <= '9') return c - '0';
    if ('a' <= c && c <= 'f') return 10 + (c - 'a');
    if ('A' <= c && c <= 'F') return 10 + (c - 'A');
    return -1;
}

/* кодпоинт (U+XXXXX) → UTF-8 */
static inline void utf8_from_codepoint(unsigned cp) {
    if (cp <= 0x7F) {
        str_putc((char)cp);
    } else if (cp <= 0x7FF) {
        str_putc((char)(0xC0 | ((cp >> 6) & 0x1F)));
        str_putc((char)(0x80 | (cp & 0x3F)));
    } else if (cp <= 0xFFFF) {
        str_putc((char)(0xE0 | ((cp >> 12) & 0x0F)));
        str_putc((char)(0x80 | ((cp >> 6) & 0x3F)));
        str_putc((char)(0x80 | (cp & 0x3F)));
    } else if (cp <= 0x10FFFF) {
        str_putc((char)(0xF0 | ((cp >> 18) & 0x07)));
        str_putc((char)(0x80 | ((cp >> 12) & 0x3F)));
        str_putc((char)(0x80 | ((cp >> 6) & 0x3F)));
        str_putc((char)(0x80 | (cp & 0x3F)));
    } else {
        utf8_from_codepoint(0xFFFD);
    }
}

static inline void str_reset() {
    string_pos = 0;
    string_buf[0] = '\0';
}

%}


%%


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


"--"                    { comm_reset(); comment_start_line = yylineno; BEGIN(SCOMM); }
"--[["                  { comm_reset(); comment_start_line = yylineno; BEGIN(MCOMM); }


<SCOMM>[^\n]*           { cout << "Single comment: " << yytext << '\n'; BEGIN(INITIAL); }

<MCOMM>"]]"             { cout << "Multi comment: " << comment_buf << '\n'; BEGIN(INITIAL); } /* конец многострочного комментария */
<MCOMM>\n               { comm_append("\n", 1); }
<MCOMM>.                { comm_append(yytext, yyleng); }


<MCOMM><<EOF>>          { cout << "ERROR: unterminated multiline comment (opened at line " << comment_start_line << ")\n"; BEGIN(INITIAL); }


\"                      { str_reset(); BEGIN(DSTRING); } /* Старт строки с " */
\'                      { str_reset(); BEGIN(SSTRING); } /* Старт строки с ' */


<DSTRING>[^"\\\n]+      { str_append(yytext, yyleng); }              
<SSTRING>[^'\\\n]+      { str_append(yytext, yyleng); }


<DSTRING,SSTRING>\\a    { str_putc('\a'); }
<DSTRING,SSTRING>\\b    { str_putc('\b'); }
<DSTRING,SSTRING>\\f    { str_putc('\f'); }
<DSTRING,SSTRING>\\n    { str_putc('\n'); }
<DSTRING,SSTRING>\\r    { str_putc('\r'); }
<DSTRING,SSTRING>\\t    { str_putc('\t'); }
<DSTRING,SSTRING>\\v    { str_putc('\v'); }
<DSTRING>"\\\""         { str_putc('"');  }
<SSTRING>"\\'"          { str_putc('\''); }
<DSTRING,SSTRING>\\\\   { str_putc('\\'); }


<DSTRING,SSTRING>\\x[0-9A-Fa-f]{2} {
    int hi = hexval(yytext[2]);
    int lo = hexval(yytext[3]);
    str_putc((char)((hi << 4) | lo));
}


<DSTRING,SSTRING>\\[0-9]{1,3} {
    int v = std::strtol(yytext + 1, nullptr, 10);
    if (v < 0) v = 0;
    if (v > 255) v = 255;
    str_putc((char)v);
}


<DSTRING,SSTRING>\\u\{[0-9A-Fa-f]+\} {
    unsigned cp = 0;
    for (int i = 3; yytext[i] != '}'; ++i) {
        int v = hexval(yytext[i]);
        if (v < 0) { cp = 0xFFFD; break; }
        cp = (cp << 4) | (unsigned)v;
        if (cp > 0x10FFFF) { cp = 0xFFFD; break; }
    }
    utf8_from_codepoint(cp);
}


<DSTRING,SSTRING>\\\n  { str_putc('\n'); }


<DSTRING>\"             { cout << "String: " << string_buf << '\n'; BEGIN(INITIAL); }
<SSTRING>\'             { cout << "String: " << string_buf << '\n'; BEGIN(INITIAL); }


<DSTRING>\n             { cout << "ERROR: unterminated string (\") at line " << yylineno << '\n'; BEGIN(INITIAL); }
<SSTRING>\n             { cout << "ERROR: unterminated string (') at line " << yylineno << '\n'; BEGIN(INITIAL); }


<DSTRING><<EOF>>        { cout << "ERROR: unterminated string (\") before EOF\n"; BEGIN(INITIAL); }
<SSTRING><<EOF>>        { cout << "ERROR: unterminated string (') before EOF\n"; BEGIN(INITIAL); }

<DSTRING,SSTRING>\\([^0-9abfnrtv\"\'\\xu\n]) {
    cout << "ERROR: invalid escape '" << yytext << "' at line " << yylineno << '\n';
    str_append(yytext + 1, yyleng - 1); // добавим символ после '\' буквально
}


{HEX_FLOAT}             { cout << "Float(hex): " << strtod(yytext, nullptr) << '\n'; }
{HEX_INT}               { cout << "Int(hex): " << strtoll(yytext, nullptr, 0) << '\n'; }
{DEC_FLOAT}             { cout << "Float: " << strtod(yytext, nullptr) << '\n'; }
{DEC_INT}               { cout << "Int: " << strtoll(yytext, nullptr, 10) << '\n'; }


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


"("                     { cout << "LParen: "  << yytext << '\n'; }
")"                     { cout << "RParen: "  << yytext << '\n'; }
"["                     { cout << "LBracket: "<< yytext << '\n'; }
"]"                     { cout << "RBracket: "<< yytext << '\n'; }
"{"                     { cout << "LBrace: "  << yytext << '\n'; }
"}"                     { cout << "RBrace: "  << yytext << '\n'; }


{ID_START}{ID_CONT}     { cout << "Identifier: " << yytext << '\n'; }





{WS}            ;

%%



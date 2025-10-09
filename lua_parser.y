%{
#include <iostream>
#include <string>
#include <cstdlib>
#include <cstdio>
#include <FlexLexer.h>

using namespace std;

extern yyFlexLexer *lexer;

int yylex() {
    return lexer->yylex();
}

void yyerror(const char *s) {
    cerr << "Error: " << s << endl;
}

%}

%token NUM
%left '+' '-'
%left '*' '/'

%%

program:
    | program statement
    ;

statement:
      NUM '+' NUM  { cout << $1 + $3 << endl; }
    | NUM '-' NUM  { cout << $1 - $3 << endl; }
    ;

%%


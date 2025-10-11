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

%union {
    int Int;
    char *ID;
    double Double;
    char *String;
}

%token TRUE FALSE NIL
%token IF ELSE ELSEIF
%token FOR WHILE UNTIL REPEAT BREAK
%token FUNCTION THEN DO END RETURN
%token IN LOCAL GOTO
%token VARARG

%token <Double> FLOAT
%token <Int> INT
%token <ID> ID
%token <String> STRING

%right '='
%left OR
%left AND
%left '<' '>' LESS_EQUAL GREATER_EQUAL EQUALITY INEQUALITY
%right CONC
%left '+' '-'
%left '*' '/' INT_DIV '%'
%left NOT '#' UMINUS
%right '^'
%nonassoc '.' ':' '[' ']'
%nonassoc '(' ')'

%start program

%%

program: stmt_list_em
       ;

stmt: expr '=' expr
    | stmt ';'
    ;

stmt_list_em: /* empty*/
            | stmt_list
            ;

stmt_list: stmt
         | stmt_list stmt
         ;

expr: INT
    | FLOAT
    | ID
    | STRING
    | TRUE
    | FALSE
    | NIL
    | '(' expr ')'
    | expr '+' expr
    | expr '-' expr
    | expr '*' expr
    | expr '/' expr
    | expr '%' expr
    | expr '^' expr
    | expr '<' expr
    | expr '>' expr
    | expr INT_DIV expr
    | expr OR expr
    | expr AND expr
    | expr LESS_EQUAL expr
    | expr GREATER_EQUAL expr
    | expr EQUALITY expr
    | expr INEQUALITY expr
    | expr CONC expr
    | '#' expr
    | NOT expr
    | '-' expr %prec UMINUS
    ;

expr_list_em: /* empty*/
            | expr_list
            ;

expr_list: expr
         | expr_list ',' expr
         ;
%%


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

stmt: stmt ';'
    | func_call // generate reduce/reduce conflist with symbols '-' and ')' that reduced to expr and I this it's ok
    | var_declarator_list
    | if_stmt
    ;

stmt_list_em: /* empty*/
            | stmt_list
            ;

stmt_list: stmt
         | stmt_list stmt
         ;

var_declarator_list: LOCAL variable_list '=' expr_list
                   | variable_list '=' expr_list
                   ;

variable_list: variable
       | variable_list ',' variable
       ;

if_stmt: IF expr THEN stmt_list_em END
       | IF expr THEN stmt_list_em ELSE stmt_list_em END
       | IF expr THEN stmt_list_em elseif_stmts END
       | IF expr THEN stmt_list_em elseif_stmts ELSE stmt_list_em END
       ;

elseif_stmts: elseif_stmt
            | elseif_stmts elseif_stmt
            ;

elseif_stmt: ELSEIF expr THEN stmt_list_em
           ;

variable: ID
        | variable '.' ID
        | variable '[' expr ']'
        ;

func_call: variable ':' ID '(' function_arguments_call_em ')'
         | variable '(' function_arguments_call_em ')'
         | func_call ':' ID '(' function_arguments_call_em ')'
         | func_call '(' function_arguments_call_em ')'
         ;

expr: INT
    | FLOAT
    | variable
    | STRING
    | TRUE
    | FALSE
    | NIL
    | func_call
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

function_arguments_call_em: /* empty */
                          | function_arguments_call
                          ;

function_arguments_call: expr
                       | VARARG
                       | function_arguments_call ',' expr
                       | function_arguments_call ',' VARARG
                       ;
%%


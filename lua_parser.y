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

%start program

%%

program: stmt_list_em
       ;

stmt: expr
    | stmt ';'
    | global_var_declarator_list
    | local_var_declaration_list
    | if_stmt
    | for_stmt
    | while_stmt
    | repeat_until_stmt
    ;

stmt_list_em: /* empty*/
            | stmt_list
            ;

stmt_list: stmt
         | stmt_list stmt
         ;

local_var_declaration_list: LOCAL id_list
                          | LOCAL id_list '=' expr_list
                          ;

global_var_declarator_list: id_list '=' expr_list
                   ;

id_list: ID
       | id_list ID
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

for_stmt: FOR ID '=' expr ',' expr DO stmt_list_em END
        | FOR ID '=' expr ',' expr ',' expr DO stmt_list_em END
        | FOR id_list IN expr DO stmt_list_em END
        ;

while_stmt: WHILE expr THEN stmt_list_em END
          ;

repeat_until_stmt: REPEAT stmt_list_em UNTIL expr
                 ;

expr: INT
    | FLOAT
    | ID
    | STRING
    | TRUE
    | FALSE
    | NIL
    | tableconstructor
    | '(' expr ')'
    | expr '+' expr
    | expr '-' expr
    | expr '*' expr
    | expr '/' expr
    | expr '%' expr
    | expr '^' expr
    | expr '=' expr
    | expr '<' expr
    | expr '>' expr
    | expr '[' expr ']'
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

tableconstructor: '{' field_list_em '}'
                ;

field_list_em: /* empty */
             | field_list
             ;

field_list: field
          | field_list ',' field
          | field_list ';' field
          ;

field: ID '=' expr
     | '[' expr ']' '=' expr
     | expr
     ;


expr_list_em: /* empty*/
            | expr_list
            ;

expr_list: expr
         | expr_list ',' expr
         ;
%%


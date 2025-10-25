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
%token IN LOCAL GOTO LABEL
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
%right NOT '#' UMINUS
%right '^'
%nonassoc '(' ')'

%start chunk

%%

chunk: block
     ;

block: stmt_list_em finish_stmt
     ;

stmt: ';'
    | variable_list '=' expr_list
    | function_call
    | FUNCTION func_name '(' par_list_em ')' block END
    | LOCAL FUNCTION ID '(' par_list_em ')' block END
    | LOCAL name_list
    | LOCAL name_list '=' expr_list
    | if_stmt
    | for_stmt
    | while_stmt
    | repeat_stmt
    | DO block END
    | goto_stmt
    | LABEL
    ;

stmt_list: stmt
         | stmt_list stmt
         ;

stmt_list_em: /* empty*/
            | stmt_list
            ;

if_stmt: IF expr THEN block END
       | IF expr THEN block ELSE block END
       | IF expr THEN block elseif_stmt_list END
       | IF expr THEN block elseif_stmt_list ELSE block END
       ;

elseif_stmt: ELSEIF expr THEN block
           ;

elseif_stmt_list: elseif_stmt
                | elseif_stmt_list elseif_stmt
                ;

for_stmt: FOR ID '=' expr ',' expr DO block END
        | FOR ID '=' expr ',' expr ',' expr DO block END
        | FOR name_list IN expr_list DO block END
        ;

while_stmt: WHILE expr DO block END
          ;

repeat_stmt: REPEAT block UNTIL expr
           ;

goto_stmt: GOTO ID
         ;

finish_stmt: /* empty */
           | BREAK
           | RETURN expr_list_em
           | RETURN expr_list_em ';'
           ;

name_list: ID
         | name_list ',' ID
         ;

variable: ID
        | variable '.' ID
        | variable '[' expr ']'
        | function_call '.' ID
        | function_call '[' expr ']'
        ;

variable_list: variable
       | variable_list ',' variable
       ;

variable_list_em: /* empty */
                | variable_list
                ;

par_list: name_list
        | name_list ',' VARARG
        | VARARG
        ;

par_list_em: /* empty */
           | par_list
           ;

dotted_name: ID
           | dotted_name '.' ID
           ;

func_name: dotted_name
         | dotted_name ':' ID
         ;

args: '(' expr_list_em ')'
    | tableconstructor
    | STRING
    ;

function_call: variable args
             | variable ':' ID args
             | function_call args
             | function_call ':' ID args
             ;

tableconstructor: '{' field_list_em '}'
                ;

field_list_em: /* empty */
             | field_list
             ;

field_list: field
          | field_list field_sep field
          ;

field: '[' expr ']' '=' expr
     | ID '=' expr
     | expr
     ;

field_sep: ','
         | ';'
         ;

expr: INT
    | FLOAT
    | STRING
    | TRUE
    | FALSE
    | NIL
    | VARARG
    | FUNCTION '(' par_list_em ')' block END
    | tableconstructor
    | variable
    | function_call
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

expr_list: expr
         | expr_list ',' expr
         ;

expr_list_em: /* empty */
            | expr_list
            ;


%%
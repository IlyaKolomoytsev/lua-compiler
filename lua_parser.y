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

%code requires {
    #include <string>
    #include "nodes/ExpressionNode.h"
    #include "nodes/StatementNode.h"
    #include "nodes/Program.h"
}

%union {
    int64_t Int;
    std::string* ID;
    double Float;
    std::string* String;
    ExpressionNode* exressionNode;
    StatementNode* statementNode;
    ExpressionNodeList* expressionNodeList;
    StatementNodeList* statementNodeList;
    NameList* variableList;
    ExpressionNode* variable;
}

%token TRUE FALSE NIL
%token IF ELSE ELSEIF
%token FOR WHILE UNTIL REPEAT BREAK
%token FUNCTION THEN DO END RETURN
%token IN LOCAL GOTO
%token VARARG
%token LABEL_SEP

%token <Float> FLOAT
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

%type <statementNode> chunk;
%type <statementNode> block;
%type <statementNode> stmt;
%type <statementNode> finish_stmt;
%type <statementNodeList> stmt_list;
%type <statementNodeList> stmt_list_em;
%type <exressionNode> expr;
%type <expressionNodeList> expr_list;
%type <expressionNodeList> expr_list_em;
%type <variableList> variable_list;
%type <variableList> variable_list_em;
%type <variable> variable;

%start chunk

%%

chunk: block { Program::addChunk($1); }
     ;

block: stmt_list_em finish_stmt { $$ = StatementNode::Block($1, $2); }
     ;

stmt: ';'
    | variable_list '=' expr_list { $$ = StatementNode::Assignment(Scope::Global, $1, $3); }
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
    | GOTO ID
    | LABEL_SEP ID LABEL_SEP
    ;

stmt_list: stmt { $$ = new StatementNodeList{$1}; }
         | stmt_list stmt { ($1)->push_back($2); $$ = $1; }
         ;

stmt_list_em: /* empty*/ { $$ = new StatementNodeList{}; }
            | stmt_list { $$ = $1; }
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

finish_stmt: /* empty */ { $$ = nullptr; }
           | BREAK
           | RETURN expr_list_em
           ;

name_list: ID
         | name_list ',' ID
         ;

variable: ID { $$ = ExpressionNode::Id($1); }
        | variable '.' ID { $$ = ExpressionNode::TableField($1, $3); }
        | variable '[' expr ']' { $$ = ExpressionNode::TableFieldByIndex($1, $3); }
        | function_call '.' ID
        | function_call '[' expr ']'
        ;

variable_list: variable { $$ = new NameList{$1}; }
       | variable_list ',' variable { ($1)->push_back($3); $$ = $1; }
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
    | '{' field_list_em '}'
    | STRING
    ;

function_call: variable args
             | variable ':' ID args
             | function_call args
             | function_call ':' ID args
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

expr: INT { $$ = ExpressionNode::Int($1); }
    | FLOAT { $$ = ExpressionNode::Float($1); }
    | STRING { $$ = ExpressionNode::String($1); }
    | TRUE { $$ = ExpressionNode::Bool(true); }
    | FALSE { $$ = ExpressionNode::Bool(false); }
    | NIL { $$ = ExpressionNode::Nil(); }
    | VARARG { $$ = ExpressionNode::Vararg(); }
    | FUNCTION '(' par_list_em ')' block END
    | '{' field_list_em '}'
    | variable
    | function_call
    | '(' expr ')'
    | expr '+' expr { $$ = ExpressionNode::Summation($1, $3); }
    | expr '-' expr { $$ = ExpressionNode::Subtraction($1, $3); }
    | expr '*' expr { $$ = ExpressionNode::Multiplication($1, $3); }
    | expr '/' expr { $$ = ExpressionNode::Division($1, $3); }
    | expr '%' expr { $$ = ExpressionNode::Modulo($1, $3); }
    | expr '^' expr { $$ = ExpressionNode::Exponentiation($1, $3); }
    | expr '<' expr { $$ = ExpressionNode::Less($1, $3); }
    | expr '>' expr { $$ = ExpressionNode::Greater($1, $3); }
    | expr INT_DIV expr { $$ = ExpressionNode::IntegerDivision($1, $3); }
    | expr OR expr { $$ = ExpressionNode::Or($1, $3); }
    | expr AND expr { $$ = ExpressionNode::And($1, $3); }
    | expr LESS_EQUAL expr { $$ = ExpressionNode::LessEqual($1, $3); }
    | expr GREATER_EQUAL expr { $$ = ExpressionNode::GreaterEqual($1, $3); }
    | expr EQUALITY expr { $$ = ExpressionNode::Equality($1, $3); }
    | expr INEQUALITY expr { $$ = ExpressionNode::Unequality($1, $3); }
    | expr CONC expr { $$ = ExpressionNode::Concatenation($1, $3); }
    | '#' expr { $$ = ExpressionNode::Length($2); }
    | NOT expr { $$ = ExpressionNode::Negation($2); }
    | '-' expr %prec UMINUS { $$ = ExpressionNode::UnaryMinus($2); }
    ;

expr_list: expr { $$ = new ExpressionNodeList{$1}; }
         | expr_list ',' expr { ($1)->push_back($3); $$ = $1; }
         ;

expr_list_em: /* empty */
            | expr_list
            ;


%%
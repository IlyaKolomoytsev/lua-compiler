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
    ExpressionNode* expressionNode;
    StatementNode* statementNode;
    ExpressionNodeList* expressionNodeList;
    StatementNodeList* statementNodeList;
    NameList* nameList;
    DottedNameList* dottedNameList;
    ExpressionNode* variable;
    TableField* tableField;
    TableFieldList* tableFieldList;
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
%type <statementNode> while_stmt;
%type <statementNode> repeat_stmt;
%type <statementNode> for_stmt;
%type <statementNode> if_stmt;
%type <statementNode> elseif_stmt;
%type <statementNode> elseif_stmt_list;
%type <statementNodeList> stmt_list;
%type <statementNodeList> stmt_list_em;
%type <expressionNode> expr;
%type <expressionNode> function_call;
%type <expressionNodeList> expr_list;
%type <expressionNodeList> expr_list_em;
%type <expressionNodeList> args;
%type <nameList> variable_list;
%type <nameList> variable_list_em;
%type <nameList> name_list;
%type <nameList> par_list;
%type <nameList> par_list_em;
%type <dottedNameList> dotted_name;
%type <dottedNameList> func_name;
%type <variable> variable;
%type <tableField> field;
%type <tableFieldList> field_list;
%type <tableFieldList> field_list_em;

%start chunk

%%

chunk: block { Program::addChunk($1); }
     ;

block: stmt_list_em finish_stmt { $$ = StatementNode::Block($1, $2); }
     ;

stmt: ';'
    | variable_list '=' expr_list { $$ = StatementNode::Assignment(Scope::Global, $1, $3); }
    | function_call { $$ = StatementNode::FunctionCall($1); }
    | FUNCTION func_name '(' par_list_em ')' block END
    | LOCAL FUNCTION ID '(' par_list_em ')' block END
    | LOCAL name_list { $$ = StatementNode::Declaration(Scope::Local, $2); }
    | LOCAL name_list '=' expr_list { $$ = StatementNode::Assignment(Scope::Local, $2, $4); }
    | if_stmt { $$ = $1; }
    | for_stmt { $$ = $1; }
    | while_stmt { $$ = $1; }
    | repeat_stmt { $$ = $1; }
    | DO block END { $$ = StatementNode::DoBlock($2); }
    | GOTO ID { $$ = StatementNode::GoTo($2); }
    | LABEL_SEP ID LABEL_SEP { $$ = StatementNode::Label($2); }
    ;

stmt_list: stmt { $$ = new StatementNodeList{$1}; }
         | stmt_list stmt { ($1)->push_back($2); $$ = $1; }
         ;

stmt_list_em: /* empty*/ { $$ = new StatementNodeList{}; }
            | stmt_list { $$ = $1; }
            ;

if_stmt: IF expr THEN block END { $$ = StatementNode::Branching($2, $4); }
       | IF expr THEN block ELSE block END { $$ = StatementNode::Branching($2, $4, $6); }
       | IF expr THEN block elseif_stmt_list END { $$ = StatementNode::Branching($2, $4, $5); }
       | IF expr THEN block elseif_stmt_list ELSE block END { $$ = StatementNode::Branching($2, $4, StatementNode::BranchingChain($5, $7)); }
       ;

elseif_stmt: ELSEIF expr THEN block { $$ = StatementNode::Branching($2, $4); }
           ;

elseif_stmt_list: elseif_stmt { $$ = $1; }
                | elseif_stmt_list elseif_stmt {$$ = StatementNode::BranchingChain($1, $2); }
                ;

for_stmt: FOR ID '=' expr ',' expr DO block END { ForRangeStruct r; r.start = $4; r.finish = $6; r.step = ExpressionNode::Int(1); $$ = StatementNode::ForLoop(ExpressionNode::Id($2), r, $8); }
        | FOR ID '=' expr ',' expr ',' expr DO block END { ForRangeStruct r; r.start = $4; r.finish = $6; r.step = $8;  $$ = StatementNode::ForLoop(ExpressionNode::Id($2), r, $10); }
        | FOR name_list IN expr_list DO block END { $$ = StatementNode::ForLoop($2, $4, $6); }
        ;

while_stmt: WHILE expr DO block END { $$ = StatementNode::WhileLoop($2, $4); }
          ;

repeat_stmt: REPEAT block UNTIL expr { $$ = StatementNode::RepeatLoop($2, $4); }
           ;

finish_stmt: /* empty */ { $$ = nullptr; }
           | BREAK { $$ = StatementNode::Break(); }
           | RETURN expr_list_em { $$ = StatementNode::Return($2); }
           ;

name_list: ID { $$ = new NameList{ ExpressionNode::Id($1) }; }
         | name_list ',' ID { ($1)->push_back( ExpressionNode::Id($3) ); $$ = $1; }
         ;

variable: ID { $$ = ExpressionNode::Id($1); }
        | variable '.' ID { $$ = ExpressionNode::TableField($1, ExpressionNode::Id($3)); }
        | variable '[' expr ']' { $$ = ExpressionNode::TableFieldByIndex($1, $3); }
        | function_call '.' ID { $$ = ExpressionNode::TableField($1, ExpressionNode::Id($3)); }
        | function_call '[' expr ']' { $$ = ExpressionNode::TableFieldByIndex($1, $3); }
        ;

variable_list: variable { $$ = new NameList{$1}; }
       | variable_list ',' variable { ($1)->push_back($3); $$ = $1; }
       ;

variable_list_em: /* empty */ { $$ = new NameList(); }
                | variable_list { $$ = $1; }
                ;

par_list: name_list { $$ = $1; }
        | name_list ',' VARARG { ($1)->push_back(ExpressionNode::Vararg()); $$ = $1; }
        | VARARG { $$ = new NameList{ExpressionNode::Vararg()}; }
        ;

par_list_em: /* empty */ { $$ = new NameList(); }
           | par_list { $$ = $1; }
           ;

dotted_name: ID { $$ = new DottedNameList{$1}; }
           | dotted_name '.' ID { ($1)->push_back($3); $$ = $1; }
           ;

func_name: dotted_name { $$ = $1; }
         | dotted_name ':' ID { ($1)->push_back($3); $$ = $1; }
         ;

args: '(' expr_list_em ')' { $$ = $2; }
    | '{' field_list_em '}' { $$ = new ExpressionNodeList { ExpressionNode::TableConstructor($2)}; }
    | STRING { $$ = new ExpressionNodeList { ExpressionNode::String($1)}; }
    ;

function_call: variable args { $$ = ExpressionNode::FunctionCall($1, $2); }
             | variable ':' ID args { $$ = ExpressionNode::TableFunctionCall($1, ExpressionNode::Id($3), $4); }
             | function_call args { $$ = ExpressionNode::FunctionCall($1, $2); }
             | function_call ':' ID args { $$ = ExpressionNode::TableFunctionCall($1, ExpressionNode::Id($3), $4); }
             ;

field_list_em: /* empty */ { $$ = new TableFieldList{}; }
             | field_list { $$ = $1; }
             ;

field_list: field { $$ = new TableFieldList(); $$->push_back(*$1); delete $1; }
          | field_list field_sep field { ($1)->push_back(*$3); delete $3; $$ = $1; }
          ;

field: '[' expr ']' '=' expr { $$ = new TableField{$2, $5}; }
     | ID '=' expr { $$ = new TableField{ExpressionNode::String($1), $3}; }
     | expr { $$ = new TableField{nullptr, $1}; }
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
    | FUNCTION '(' par_list_em ')' block END { $$ = ExpressionNode::FunctionLiteral($3, $5); }
    | '{' field_list_em '}' { $$ = ExpressionNode::TableConstructor($2); }
    | variable { $$ = $1; }
    | function_call { $$ = $1; }
    | '(' expr ')' { $$ = $2; }
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

expr_list_em: /* empty */ { $$ = new ExpressionNodeList{}; }
            | expr_list { $$ = $1; }
            ;


%%
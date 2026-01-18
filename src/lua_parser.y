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
    #include "node/NodeExpressionModule.h"
    #include "node/NodeStatementModule.h"
    #include "node/statement/StatementNode.h"
    #include "node/Program.h"
    #include "node/Parser.h"
}

%union {
    int64_t Int;
    std::string* ID;
    double Float;
    std::string* String;
    ExpressionNode* expressionNode;
    StatementNode* statementNode;
    BlockStmtNode* blockStatementNode;
    BranchingStmtNode* branchingStmtNode;
    ExpressionNodeList* expressionNodeList;
    StatementNodeList* statementNodeList;
    DottedNameStruct* dottedNameStruct;
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
%type <blockStatementNode> block;
%type <statementNode> stmt;
%type <statementNode> finish_stmt;
%type <statementNode> while_stmt;
%type <statementNode> repeat_stmt;
%type <statementNode> for_stmt;
%type <statementNode> if_stmt;
%type <branchingStmtNode> elseif_stmt;
%type <branchingStmtNode> elseif_stmt_list;
%type <statementNodeList> stmt_list;
%type <statementNodeList> stmt_list_em;
%type <expressionNode> expr;
%type <expressionNode> function_call;
%type <expressionNodeList> expr_list;
%type <expressionNodeList> expr_list_em;
%type <expressionNodeList> args;
%type <expressionNodeList> variable_list;
%type <expressionNodeList> variable_list_em;
%type <expressionNodeList> name_list;
%type <expressionNodeList> par_list;
%type <expressionNodeList> par_list_em;
%type <dottedNameStruct> dotted_name;
%type <dottedNameStruct> func_name;
%type <variable> variable;
%type <tableField> field;
%type <tableFieldList> field_list;
%type <tableFieldList> field_list_em;

%start chunk

%%

chunk: block { Program::addChunk($1); }
     ;

block: stmt_list_em finish_stmt { $$ = parser::Block($1, $2); }
     ;

stmt: stmt ';' { $$ = $1; }
    | variable_list '=' expr_list { $$ = new AssignmentStmtNode(Scope::Global, $1, $3); }
    | function_call { $$ = StatementNode::FunctionCall($1); }
    | FUNCTION func_name '(' par_list_em ')' block END { $$ = StatementNode::FunctionDeclaration($2, $4, $6); }
    | LOCAL FUNCTION ID '(' par_list_em ')' block END { $$ = StatementNode::FunctionDeclaration(new IdExprNode($3), $5, $7); }
    | LOCAL name_list { $$ = StatementNode::Declaration(Scope::Local, $2); }
    | LOCAL name_list '=' expr_list { $$ = new AssignmentStmtNode(Scope::Local, $2, $4); }
    | if_stmt { $$ = $1; }
    | for_stmt { $$ = $1; }
    | while_stmt { $$ = $1; }
    | repeat_stmt { $$ = $1; }
    | DO block END { $$ = $2; }
    | GOTO ID { $$ = StatementNode::GoTo($2); }
    | LABEL_SEP ID LABEL_SEP { $$ = StatementNode::Label($2); }
    ;

stmt_list: stmt { $$ = new StatementNodeList{$1}; }
         | stmt_list stmt { ($1)->push_back($2); $$ = $1; }
         ;

stmt_list_em: /* empty*/ { $$ = new StatementNodeList{}; }
            | stmt_list { $$ = $1; }
            ;

if_stmt: IF expr THEN block END { $$ = new BranchingStmtNode($2, $4); }
       | IF expr THEN block ELSE block END { $$ = new BranchingStmtNode($2, $4, $6); }
       | IF expr THEN block elseif_stmt_list END { $$ = new BranchingStmtNode($2, $4, $5); }
       | IF expr THEN block elseif_stmt_list ELSE block END { $$ = parser::IfElseifChainElse($2, $4, $5, $7); }
       ;

elseif_stmt: ELSEIF expr THEN block { $$ = new BranchingStmtNode($2, $4); }
           ;

elseif_stmt_list: elseif_stmt { $$ = $1; }
                | elseif_stmt_list elseif_stmt {$$ = parser::ContinueElseifBranching($1, $2); }
                ;

for_stmt: FOR ID '=' expr ',' expr DO block END { $$ = new ForLoopClassicStmtNode(new IdExprNode($2), {$4, $6, new IntegerExprNode(1)}, $8); }
        | FOR ID '=' expr ',' expr ',' expr DO block END { $$ = new ForLoopClassicStmtNode(new IdExprNode($2), {$4, $6, $8}, $10); }
        | FOR name_list IN expr_list DO block END { $$ = StatementNode::ForLoop($2, $4, $6); }
        ;

while_stmt: WHILE expr DO block END { $$ = StatementNode::WhileLoop($2, $4); }
          ;

repeat_stmt: REPEAT block UNTIL expr { $$ = StatementNode::RepeatLoop($2, $4); }
           ;

finish_stmt: /* empty */ { $$ = nullptr; }
           | BREAK { $$ = new BreakStmtNode(); }
           | RETURN expr_list_em { $$ = StatementNode::Return($2); }
           | finish_stmt ';' { $$ = $1; }
           ;

name_list: ID { $$ = new ExpressionNodeList{ new IdExprNode($1) }; }
         | name_list ',' ID { ($1)->push_back( new IdExprNode($3) ); $$ = $1; }
         ;

variable: ID { $$ = new IdExprNode($1); }
        | variable '.' ID { $$ = new TableFieldExprNode($1, new IdExprNode($3)); }
        | variable '[' expr ']' { $$ = new TableFieldExprNode($1, $3); }
        | function_call '.' ID { $$ = new TableFieldExprNode($1, new IdExprNode($3)); }
        | function_call '[' expr ']' { $$ = new TableFieldExprNode($1, $3); }
        ;

variable_list: variable { $$ = new ExpressionNodeList{$1}; }
       | variable_list ',' variable { ($1)->push_back($3); $$ = $1; }
       ;

variable_list_em: /* empty */ { $$ = new ExpressionNodeList(); }
                | variable_list { $$ = $1; }
                ;

par_list: name_list { $$ = $1; }
        | name_list ',' VARARG { ($1)->push_back(new VarargExprNode()); $$ = $1; }
        | VARARG { $$ = new ExpressionNodeList{new VarargExprNode()}; }
        ;

par_list_em: /* empty */ { $$ = new ExpressionNodeList(); }
           | par_list { $$ = $1; }
           ;

dotted_name: ID { $$ = new DottedNameStruct(std::move(*$1)); delete $1; }
           | dotted_name '.' ID { $$ = $1->nextName(std::move(*$3)); delete $3; }
           ;

func_name: dotted_name { $$ = $1; }
         | dotted_name ':' ID { $$ = $1->nextMethod(std::move(*$3)); delete $3; }
         ;

args: '(' expr_list_em ')' { $$ = $2; }
    | '{' field_list_em '}' { $$ = new ExpressionNodeList { new TableConstructorExprNode($2)}; }
    | STRING { $$ = new ExpressionNodeList { new StringExprNode($1)}; }
    ;

function_call: variable args { $$ = parser::FunctionCallWithArgs($1, $2); }
             | variable ':' ID args { $$ = parser::TableMethodCall($1, $3, $4); }
             | function_call args { $$ = parser::FunctionCallWithArgs($1, $2); }
             | function_call ':' ID args {  $$ = parser::TableMethodCall($1, $3, $4); }
             ;

field_list_em: /* empty */ { $$ = new TableFieldList{}; }
             | field_list { $$ = $1; }
             ;

field_list: field { $$ = new TableFieldList(); $$->push_back(*$1); delete $1; }
          | field_list field_sep field { ($1)->push_back(*$3); delete $3; $$ = $1; }
          ;

field: '[' expr ']' '=' expr { $$ = new TableField{$2, $5}; }
     | ID '=' expr { $$ = new TableField{new StringExprNode($1), $3}; }
     | expr { $$ = new TableField{nullptr, $1}; }
     ;

field_sep: ','
         | ';'
         ;

expr: INT { $$ = new IntegerExprNode($1); }
    | FLOAT { $$ = new FloatExprNode($1); }
    | STRING { $$ = new StringExprNode($1); }
    | TRUE { $$ = new BoolExprNode(true); }
    | FALSE { $$ = new BoolExprNode(false); }
    | NIL { $$ = new NilExprNode(); }
    | VARARG { $$ = new VarargExprNode(); }
    | FUNCTION '(' par_list_em ')' block END { $$ = new FunctionExprNode($3, $5); }
    | '{' field_list_em '}' { $$ = new TableConstructorExprNode($2); }
    | variable { $$ = $1; }
    | function_call { $$ = $1; }
    | '(' expr ')' { $$ = $2; }
    | expr '+' expr { $$ = new SummationExprNode($1, $3); }
    | expr '-' expr { $$ = new SubtractionExprNode($1, $3); }
    | expr '*' expr { $$ = new MultiplicationExprNode($1, $3); }
    | expr '/' expr { $$ = new DivisionExprNode($1, $3); }
    | expr '%' expr { $$ = new ModuloExprNode($1, $3); }
    | expr '^' expr { $$ = new ExponentiationExprNode($1, $3); }
    | expr '<' expr { $$ = new LessExprNode($1, $3); }
    | expr '>' expr { $$ = new GreaterExprNode($1, $3); }
    | expr INT_DIV expr { $$ = new IntegerDivision($1, $3); }
    | expr OR expr { $$ = new OrExprNode($1, $3); }
    | expr AND expr { $$ = new AndExprNode($1, $3); }
    | expr LESS_EQUAL expr { $$ = new LessEqualExprNode($1, $3); }
    | expr GREATER_EQUAL expr { $$ = new GreaterEqualExprNode($1, $3); }
    | expr EQUALITY expr { $$ = new EqualityExprNode($1, $3); }
    | expr INEQUALITY expr { $$ = new UnequalityExprNode($1, $3); }
    | expr CONC expr { $$ = new ConcatenationExprNode($1, $3); }
    | '#' expr { $$ = new LengthExprNode($2); }
    | NOT expr { $$ = new NegationExprNode($2); }
    | '-' expr %prec UMINUS { $$ = new UnaryMinusExprNode($2); }
    ;

expr_list: expr { $$ = new ExpressionNodeList{$1}; }
         | expr_list ',' expr { ($1)->push_back($3); $$ = $1; }
         ;

expr_list_em: /* empty */ { $$ = new ExpressionNodeList{}; }
            | expr_list { $$ = $1; }
            ;


%%
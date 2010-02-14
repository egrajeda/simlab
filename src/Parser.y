%{
#include <string>
#include <cstdio>
#include <iostream>

#include "Ast.h"
#include "Interpreter.h"

extern int yylex();
void yyerror(const char* s) { printf("ERROR: %s\n", s); }

%}

%union {
    void*                 anything;
    struct AstArguments*  arguments;
    struct AstExpression* expression;
    struct AstIdentifier* identifier;
    std::string*          string; 
};

%token <string> TIDENTIFIER TINTEGER TSTRING

%type <anything> input
%type <arguments> arguments;
%type <expression> expression number
%type <identifier> identifier

%left '+' '-'
%left '*' '/'
%left '(' ')'

%start input

%%

input : expression 
          { INTERPRETER.buildAst(*$1); }
      ;

expression : identifier '=' expression 
               { $$ = new AstAssignment(*$1, *$3); }
           | identifier '(' arguments ')'
               { $$ = new AstFunctionCall(*$1, *$3); }
           | identifier 
               { $$ = $<expression>1; }
           | number
           | TSTRING
               { $$ = new AstString(*$1); delete $1; }
           | expression '+' expression
               { $$ = new AstBinaryOperator(*$1, '+', *$3); }
           | expression '-' expression
               { $$ = new AstBinaryOperator(*$1, '-', *$3); }
           | expression '*' expression
               { $$ = new AstBinaryOperator(*$1, '*', *$3); }
           | expression '/' expression
               { $$ = new AstBinaryOperator(*$1, '/', *$3); }
           | '(' expression ')'
               { $$ = $2; }
           ;

identifier : TIDENTIFIER 
               { $$ = new AstIdentifier(*$1); delete $1; } 
           ;

number : TINTEGER 
           { $$ = new AstInteger(atol($1->c_str())); delete $1; }
       ;

arguments :
              { $$ = new AstArguments(); }
          | expression
              { $$ = new AstArguments($1); }
          | arguments ',' expression
              { $1->add($3); }
          ;

%%


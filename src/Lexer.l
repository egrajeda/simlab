%{
#include <string>

#include "Parser.hpp"

#define SAVE_TOKEN \
    yylval.string = new std::string(yytext, yyleng)
#define TOKEN(x) \
    yylval.token = x;

extern "C" int yywrap() { }

%}

%%

[ \t\n]                         ;
[a-zA-Z]*                       SAVE_TOKEN; return TIDENTIFIER;
[0-9]+                          SAVE_TOKEN; return TINTEGER;
'[^'\n]*'                       SAVE_TOKEN; return TSTRING;
"="                             return '=';
"+"                             return '+';
"-"                             return '-';
"*"                             return '*';
"/"                             return '/';
"("                             return '(';
")"                             return ')';
","                             return ',';                        
.                               printf("Token deconocido!\n"); yyterminate();

%%

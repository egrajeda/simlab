#include "Interpreter.h"
#include "Lexer.h"

extern Ast* ast;

extern int yyparse();

Ast* Interpreter::parse(const std::string& input) const
{
    YY_BUFFER_STATE buffer = yy_scan_string(input.c_str());
    yy_switch_to_buffer(buffer);
    yyparse();
    yylex_destroy();

    return ast;
}

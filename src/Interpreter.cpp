#include "Interpreter.h"
#include "Lexer.h"

extern int yyparse();

Interpreter::Interpreter() : m_ast(NULL)
{ }

Interpreter::~Interpreter() 
{
    delete m_ast;
}

Ast* Interpreter::parse(const std::string& input) const
{
    YY_BUFFER_STATE buffer = yy_scan_string(input.c_str());
    yy_switch_to_buffer(buffer);
    yyparse();
    yylex_destroy();

    return m_ast;
}

void Interpreter::buildAst(AstExpression& expression)
{
    delete m_ast;
    m_ast = new Ast(expression);
}

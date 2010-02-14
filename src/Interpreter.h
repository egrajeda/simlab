#ifndef INTERPRETER_H
#define INTERPRETER_H

#include "Ast.h"

// Interpreter
//
// Clase que se encarga de analizar las instrucciones introducidas, y crear el 
// AST.
class Interpreter
{
     Interpreter();
    ~Interpreter();

    // m_ast
    //
    // Un puntero al AST actual, si existe.
    Ast* m_ast;

  public:
    // Parse
    //
    // Crea y devuelve un AST a partir de la cadena de texto que se le pase
    // como argumento.
    Ast* parse(const std::string& input) const;

    // Instance
    //
    // Retorna la única instancia existente de esta clase, para ser usada
    // según el patrón de diseño Singleton.
    static Interpreter& Instance()
    {
        static Interpreter singleton;
        return singleton;
    }

    // buildAst
    //
    // Construye el AST a partir de los argumentos pasados por Bison.    
    void buildAst(AstExpression& expression);
};

// Un macro para utilizar esta clase más facilmente.
#define INTERPRETER Interpreter::Instance()

#endif

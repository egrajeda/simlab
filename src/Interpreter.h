#ifndef INTERPRETER_H
#define INTERPRETER_H

#include "Ast.h"

// Interpreter
//
// Clase que se encarga de analizar las instrucciones introducidas, y crear el 
// AST.
class Interpreter
{
  public:
    // Parse
    //
    // Crea y devuelve un AST a partir de la cadena de texto que se le pase
    // como argumento.
    Ast* parse(const std::string& input) const;
};

#endif

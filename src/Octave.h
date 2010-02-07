#ifndef OCTAVE_H
#define OCTAVE_H

#include <string>

// Octave
//
// Clase que envuelve a la aplicación Octave, permitiendo comunicarse con
// el y mostrar los resultados en MATA.
class Octave
{
    // Write
    //
    // Es el extremo de la tubería en la que el proceso actual (padre o hijo)
    // puede escribir para enviar información al otro proceso.
    int m_write;

    // Read
    // Es el extremo de la tubería en la que el proceso actual (padre o hijo)
    // lee la información que proviene del otro proceso.
    int m_read;

  public:
    // Default constructor
    //
    // Crea el proceso hijo con Octave corriendo en él.
    Octave(); 

    // Destructor
    //
    // Se encarga de limpiar todo, en especial salirse de Octave y no dejarlo
    // como un proceso zombie.
    ~Octave();

    // Send
    //
    // Envía un comando a Octave y se bloquea hasta obtener una respuesta,
    // para después retornarla.
    std::string send(const std::string& command) const;

    // Normalize
    //
    // Normaliza la respuesta obtenida por parte de Octave, para que exista
    // un estándar en la forma de manejar las salidas de cada programa.
    std::string normalize(std::string& answer) const;
};

#endif

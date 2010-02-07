#include <algorithm>
#include <unistd.h>
#include <string.h>

#include "Octave.h"

Octave::Octave()
{
    int pipe_child2parnt[2];
    int pipe_parnt2child[2];

    if (pipe(pipe_child2parnt)) {
        // Throw algo
    }
    if (pipe(pipe_parnt2child)) {
        // Throw algo
    }

    // Proceso hijo
    if (fork() == 0) {
        for(int fd = 0; fd < 3; ++fd)
            close(fd);
        dup2(pipe_parnt2child[0], 0);
        dup2(pipe_child2parnt[1], 1);
        if (execlp("octave", "octave", "-q", NULL) == -1) {
            // Throw algo
        } 
    }
    // Proceso padre
    else {
        m_read  = pipe_child2parnt[0];
        m_write = pipe_parnt2child[1];
    }
}

std::string Octave::send(const std::string& command) const
{
    // Mandamos el comando
    if (write(m_write, command.c_str(), command.length()) == -1) {
        // Throw algo
    }

    // Leemos la respuesta (TODO: Talvez se puede hacer sin usar buffer)
    char        buffer;
    std::string result;
    do {
        if (read(m_read, &buffer, sizeof(buffer)) == -1) {
            // Throw algo
        }
        result += buffer;
    } while (buffer != '\n');

    // Normalizamos la respuesta obtenida antes de retornar
    return normalize(result);
}

std::string Octave::normalize(std::string& answer) const
{
    // Eliminamos los espacios en blanco
    answer.erase(std::remove_if(answer.begin(), answer.end(), isspace), 
        answer.end());

    // Eliminamos el "ans=" del principio
    return answer.substr(4, answer.length()-4);
}

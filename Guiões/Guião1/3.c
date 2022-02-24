// Aqui critério de paragem é apenas o \n. E até lá lemos linha a linha.
// Ou seja, temos de ir testando os caracteres que vão sendo lidos.

//Usar ssize_t readln(int fd, char*line, size_t size);   // onde o ln acrescenta o número da linha

#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>

// $cat filename
// output: "Este texto está dentro do filename"

int main(int argc, char* args[]) {

    char* buffer[1024];

    int n;
    while((n = read(STDIN_FILENO,buffer,1)) > 0) {
        write(STDOUT_FILENO,buffer,n);
    }

}
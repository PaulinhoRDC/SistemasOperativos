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

    int i = 0;

    while( i<size && readc(fd, &buf[i]) > 0) {

        i++;
        if (((char*)buf)[i-1] == '\n'){
            return i;
        }
    }

    return i;
}

int readc(int fd, char * c){

    // implementação char a char
    return read (fd, c, 1);
}
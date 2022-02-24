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

/*
(base) paulinhordc@MacBook-Pro-de-Paulo Guião1 % gcc -o 2 2.c
(base) paulinhordc@MacBook-Pro-de-Paulo Guião1 % ./2         
ola
ola
mundo
mundo
*/
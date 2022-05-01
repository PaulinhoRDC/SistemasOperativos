#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>

#define BUFSIZE 1024

// $cat filename
// output: "Este texto está dentro do filename"

int main(int argc, char* args[]) {

    int n;
    char buffer[BUFSIZE];

    while((n = read(0,buffer,sizeof(buffer))) > 0) {
        write(1,buffer,n);
    }

    return 0;  /* EXIT_SUCCESS */

} 

/*
(base) paulinhordc@MacBook-Pro-de-Paulo Guião1 % gcc mycat.c -o mycat
(base) paulinhordc@MBP-de-Paulo Guião1 % ./mycat
ola
ola
tudo bem?
tudo bem?
adeus
adeus
*/

/*

Poderia fazer >> echo ola | ./mycat     
Aqui temos um pipe, a fazer com que ola ,seja lido como se fosse de um teclado! (como se fosse o standard input)

*/
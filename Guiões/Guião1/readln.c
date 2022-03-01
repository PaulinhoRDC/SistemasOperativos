#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>

ssize_t readln(int fd, char* line, size_t size){

    int n, nb=0;                    // VAMOS EFETUAR LEITURA BYTE A BYTE
    
    while (nb < size && (n= read(fd, line + nb, 1)) > 0  && line[nb] != '\n' ) {    
        nb++;
    }        

    if (n == -1)
        return -1;

    return nb > 0 && line[nb] == '\n' ? nb + 1 : nb;
}

int main() {
    char buffer[1024];        //PODEMOS IR ALTERANDO O VALOR DO BUFFER

    printf ("%ld \n", readln (0, buffer, sizeof(buffer)));
    return 0;
}

/*

(base) paulinhordc@MBP-de-Paulo Guião1 % gcc readln.c -o readln
(base) paulinhordc@MBP-de-Paulo Guião1 % ./readln
ola
4 

*/
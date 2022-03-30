/*
1. Escreva um programa que redireccione o descritor associado ao seu standard input para o ficheiro
/etc/passwd, e o standard output e error respectivamente para saida.txt e erros.txt. Imediatamente
antes de o programa terminar, o mesmo deve imprimir no terminal a mensagem ”terminei”.
*/

#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h> 
#include <sys/wait.h>

int main(){

    int outputoriginal = dup(1);

    int fd = open("/etc/passwd", O_RDONLY);
    dup2(fd,0);
    close(fd); 

    //OU// close(0);   fd = open("/etc/passwd", O_RDONLY);      mas aqui não podíamos ter close(fd), porque iamos estar a fechar o ficheiro

    int fd2 = open("saida.txt",O_CREAT|O_WRONLY|O_TRUNC, 0666);
    close(1);
    dup(fd2);
    close(fd2);

    int fd3 = open("erros.txt",O_CREAT|O_WRONLY|O_TRUNC, 0666);
    dup2(fd3,2);
    close(fd3);

    dup2(outputoriginal, 1);
    printf("Terminei");
    
    return 0;
    
}
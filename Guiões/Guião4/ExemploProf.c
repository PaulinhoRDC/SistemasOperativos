#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h> 
#include <sys/wait.h>

int main(){
    int fd = open("/etc/passwd", O_RDONLY);
    close(0);           //STANDARD INPUT
    dup(fd);
    close(fd); 

    //OU// close(0);   fd = open("/etc/passwd", O_RDONLY);      mas aqui não podíamos ter close(fd), porque iamos estar a fechar o ficheiro

    int fd2 = open("/tmp/saida.txt",O_CREAT|O_WRONLY|O_TRUNC, 0666);
    close(1);
    dup(fd2);
    close(fd2);

    char nome[100];
    fgets(nome, sizeof(nome), stdin);
    printf("ola, %s \n", nome);
    
    return 0;
    
}

// com  DUP2

int main2(){
    int fd = open("/etc/passwd", O_RDONLY);
    dup2(fd, 0);
    close(fd); 

    //OU// close(0);   fd = open("/etc/passwd", O_RDONLY);      mas aqui não podíamos ter close(fd), porque iamos estar a fechar o ficheiro

    int fd2 = open("/tmp/saida.txt",O_CREAT|O_WRONLY|O_TRUNC, 0666);
    dup2(fd2,1);
    close(fd2);

    char nome[100];
    fgets(nome, sizeof(nome), stdin);
    printf("ola, %s \n", nome);
    
    return 0;
    
}
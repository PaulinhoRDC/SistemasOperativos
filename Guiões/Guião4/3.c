/*
3. Modifique novamente o programa inicial de modo a que seja executado o comando wc, sem argumentos,
depois do redireccionamento dos descritores de entrada e saída. Note que, mais uma vez, as associações
– e redireccionamentos – de descritores de ficheiros são preservados pela primitiva exec().
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

    //dup2(outputoriginal, 1);                  // Se quiser que seja mostrado no terminal
    execlp("wc","wc",NULL);

    
    return 0;
    
}
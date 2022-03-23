/*
1. Implemente um programa que execute o comando ls -l. Note que no caso da execução ser bem
sucedida, mais nenhuma outra instrução é executada do programa original.
*/

#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h> 
#include <sys/wait.h>

int main(int argc, char* argv[]){

    execlp("ls", "ls", "-l",NULL);          // o argv[0] é irrelevante!

    printf("FOI USADO!");                   // TESTE

    return 1;
}
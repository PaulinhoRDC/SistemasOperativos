/*
4. Escreva um programa redir que permita executar um comando, opcionalmente redireccionando a entrada
e/ou a saída. O programa poderá ser invocado, com:
                                                     redir [-i fich_entrada] [-o fich_saida] comando arg1 arg2 ...
*/

#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h> 
#include <sys/wait.h>


int redir(char *ficheiroentrada, char *ficheirosaida, char *comando) {

    int outputOriginal = dup(1);

    int fd = open(ficheiroentrada,O_RDONLY);
    if(fd == -1) perror("Erro no open 1");
    
    dup2(fd,0);
    close(fd);

    int fd2 = open(ficheirosaida, O_CREAT | O_WRONLY | O_TRUNC, 0666);
    if(fd2 == -1) perror("Erro no open 2");
    dup2(fd2,1);
    close(fd2);

    dup2(outputOriginal,1);

    execlp(comando,comando,NULL);

    
    return 0;
} 



int main(int argc, char* argv[]) {

    //redir [-i fich_entrada] [-o fich_saida] comando arg1 arg2 ...

    char ficheiroentrada[100];
    char ficheirosaida[100];
    char comando[10];

    strcpy(ficheiroentrada,argv[1]);
    strcpy(ficheirosaida,argv[2]);
    strcpy(comando,argv[3]);

    redir(ficheiroentrada,ficheirosaida,comando);

    //printf("%s \n",ficheiroentrada);
    //printf("%s \n",ficheirosaida);




    return 0;
} 
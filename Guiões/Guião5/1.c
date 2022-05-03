/*

1. Escreva um programa que crie um pipe anónimo e de seguida crie um processo filho. Experimente o pai
enviar uma linha de texto através do descritor de escrita do pipe, e o filho receber uma linha a partir do
respectivo descritor de leitura.
Experimente de seguida provocar um atraso antes do pai enviar a linha de texto (p. ex., sleep(5)).
Note agora que a leitura do filho bloqueia enquanto o pai não realizar a operação de escrita no pipe.
Experimente agora inverter os papeis de modo à informação ser transmitida do filho para o pai.

*/

#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h> 
#include <sys/wait.h>


int filho2pai() {
    int p[2];                               // p[0] -> Leitura   p[1] -> Escrita
    char linha[] = "linha a ler";
    char buffer[20];
    int res;
    int status;


    if(pipe(p) == -1) {
        perror("Erro no pipe");
        return -1;
    }

    pid_t pid;
    pid = fork();

    if(pid==0) {

        // Como filho só vai escrever fechamos o descritor de leitura
        // fechar descritores que nao usamos é uma boa maneira de prevenir deadlock
        close(p[0]);

        write(p[1],&linha,sizeof(linha));
        printf("[Filho] Escrevi -> %s \n", linha);
        close(p[1]);

        _exit(0);
    }


    //Como o pai só vai ler fechamos o descritor de escrita
    close(p[1]);
    res = read(p[0],&buffer,sizeof(buffer));
    printf("[Pai] read -> %s <- from pipe \n", buffer);
    close(p[0]);

    wait(&status);

    return 0;
}



int pai2filho() {
    int p[2];   // p[0] -> Leitura   p[1] -> Escrita
    char linha[] = "linha a ler";
    char buffer[20];
    int res;
    int status;


    if(pipe(p) == -1) {
        perror("Erro no pipe");
        return -1;
    }

    pid_t pid;
    pid = fork();

    if(pid==0) {

        close(p[1]);
        res = read(p[0],&buffer,sizeof(buffer));
        printf("[Filho] read -> %s From pipe, res %d\n", buffer, res);
        close(p[0]);

        _exit(0);
    }


    close(p[0]);
    write(p[1],&linha,strlen(linha));
    printf("[Pai] Escrevi linha to pipe \n");
    close(p[1]);

    wait(&status);

    return 0;
}

int main() {
    pai2filho();
}
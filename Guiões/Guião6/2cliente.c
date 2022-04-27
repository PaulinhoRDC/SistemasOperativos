/*
2. Escreva um programa “servidor”, que fique a correr em background, e acrescente a um ficheiro de “log”
todas as mensagens que sejam enviadas por “clientes”. 
Escreva um programa cliente que envia para o servidor o seu argumento. Cliente e servidor devem comunicar via pipes com nome.
*/

#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h> 
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>


int main(int argc, char * argv[]) {

    int fifo = open("fifo",O_WRONLY);
    if (fifo < 0) perror("Erro fifo");

    char buffer[100];
    
    int n;
    while((n = read(0,buffer,100)) > 0) {
        write(fifo,buffer,n);
    }

    close(fifo);

    return 0;
}



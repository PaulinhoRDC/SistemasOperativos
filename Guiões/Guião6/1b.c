/*
1. Escreva três programas que irão ilustrar a operação de pipes com nome. 
O primeiro cria um pipe com nome “fifo”. 
O segundo repete para este pipe todas as linhas de texto lidas a partir do seu standard input.
O terceiro programa repete para o seu standard output todas as linhas de texto lidas a partir deste mesmo pipe.

Note que, ao contrário dos pipes anónimos, 
a abertura para escrita de um pipe com nome bloqueia até que um processo o abra para leitura, e vice-versa.

*/

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int agrc, char * argv[]){

    int fifo = open("fifo", O_WRONLY);
    if(fifo < 0) perror("Erro fifo");

    int bytes_read;
    char buffer[100];

    while((bytes_read = read(0, buffer, sizeof(buffer))) > 0){
        write(fifo, buffer, bytes_read);
    }

    close(fifo);

}
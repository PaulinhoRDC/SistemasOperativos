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

int main() {

    int fifo = open("fifo", O_RDONLY);
    if (fifo < 0) perror("Erro fifo");

    int leitura = 0;
    char buffer[1024];
    
    while((leitura = read(fifo,buffer,sizeof(buffer))) > 0) {
        write(1,buffer,leitura);
    }
    printf("Out while");

    close(fifo);

    //unlink("fifo");

    return 0;
} 
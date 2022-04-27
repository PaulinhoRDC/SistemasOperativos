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

int main(int argc, char * argv[]){

    if(mkfifo("fifo", 0600) < 0) perror("Erro fifo");

    //unlink("fifo");        MATA O PIPE

}

/*
paulinhordc@MacBook-Pro-de-Paulo Guião6 % gcc -o 1a 1a.c
paulinhordc@MacBook-Pro-de-Paulo Guião6 % ./1a                   
paulinhordc@MacBook-Pro-de-Paulo Guião6 % ls -l
total 224
-rwxr-xr-x  1 paulinhordc  staff  49472 27 Abr 17:01 1a
-rw-r--r--  1 paulinhordc  staff    692 27 Abr 17:01 1a.c
-rw-r--r--  1 paulinhordc  staff    141 27 Abr 16:59 1b.c
-rw-r--r--  1 paulinhordc  staff      0 27 Abr 16:45 1c.c
-rw-r--r--  1 paulinhordc  staff   1017 27 Abr 16:43 ExplicaçõesProf.c
prw-r--r--  1 paulinhordc  staff      0 27 Abr 16:31 exemplo
prw-------  1 paulinhordc  staff      0 27 Abr 17:01 fifo                                       -> CRIADO
-rw-r--r--@ 1 paulinhordc  staff  45647 27 Abr 16:29 guiao-06.pdf
*/
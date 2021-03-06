/*

4. Escreva um programa que emule o funcionamento do interpretador de comandos na execução encadeada
de ls /etc | wc -l.

*/

#include <unistd.h>
#include <stdio.h>

int main(){

    int pd[2];
    pipe(pd);

    switch(fork()) {
        case 0: /* filho */                          
                close(pd[0]);

                dup2(pd[1], 1);                 //fechar canais desnecessários
                close(pd[1]);

                execlp("ls", "ls", "/etc", NULL);
                perror("ls");

                _exit(1);

        case -1: /* pai  erro */
                perror("fork");
                return 1; /*EXIT_FAILURE */

        default: /* pai sucesso */
                close(pd[1]);

                dup2(pd[0], 0);
                close(pd[0]);
                
                execlp("wc", "wc", "-l", NULL);                     //FAZEMOS WC NO PAI, PARA QUE O PAI NÃO TENHA DE ESPERAR PELO FILHO             
                perror("wc");                                       //LOGO O PAI FAZ O ÚLTIMO COMANDO NO ENCADEAMENTO DE COMANDOS QUE TEMOS
                                                                    //ISTO, PORQUE A SHELL DETETA A MORTE DO PAI E AVANÇA, E O FILHO AINDA NÃO "MORREU"
                _exit(1);


    }
    return 0;  /* EXIT_SUCCESS => #include <stdlib.h>  */
}
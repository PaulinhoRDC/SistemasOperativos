/*
3. Implemente um programa que execute concorrentemente uma lista de executáveis especificados como
argumentos da linha de comando. Considere os executáveis sem quaisquer argumentos próprios. O
programa deverá esperar pelo fim da execução de todos processos por si criados.
*/

#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h> 
#include <sys/wait.h>

int main(int argc, char* argv[]) {
    pid_t pid;
    
    // Executar em concorrencia
    for (int i=1; i != argc; i++){
        pid = fork();                                                   // cria-se um filho 
        if(pid == 0) {
            execlp (argv[i], argv[i], NULL);
            _exit(i);         // não sai com o valor esperado, pois como o execlp é executado, o exit(i) não é executado e por omissão, sai com o valor 0;
        }
    }

    for(int j=1; j != argc; j++) {
        int status;
        pid_t pid = wait(&status);
        if(WIFEXITED(status)) {
            printf("_exit: %d \n", WEXITSTATUS(status));
        }
    }
}
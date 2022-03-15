/*
4. Implemente um programa que crie dez processos filhos que deverão executar em concorrência. 
O pai deverá esperar pelo fim da execução de todos os seus filhos, imprimindo os respectivos códigos de saída.
*/

#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h> 
#include <sys/wait.h>


int main() {
    pid_t pid;
    
    // Executar em concorrencia
    for(int i=1; i<=10; i++) {
        pid = fork();
        if(pid == 0) {
            printf("Filho %d => Pid Filho: %d, Pid Pai: %d \n", i, getpid(), getppid());
            _exit(i);
        }
    }

    for(int i=1; i<=10; i++) {
        int status;
        pid_t pid = wait(&status);
        if(WIFEXITED(status)) {
            printf("Pid: %d, _exit: %d \n", pid, WEXITSTATUS(status));
        }
    }

    return 0;
}
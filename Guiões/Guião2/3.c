#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>

#include <sys/stat.h>


int main (int argc, char *argv[]) {

    pid_t pid;
    int status;

    for (int i=0; i<10; i++){
	    pid = fork();
        if(pid == 0) {
            printf("pai = %d , filho = %d \n", getppid(), getpid());
            exit(0);
        }
    }    

    //waitpid(pid,&status, WCONTINUED);

    puts("Out for");

    return 0; //não é necessário, mas por norma, quando um porgrama corre bem, devolve-se 0;
}

/*
(base) paulinhordc@MacBook-Pro-de-Paulo Guião2 % gcc 3.c -o 3
(base) paulinhordc@MacBook-Pro-de-Paulo Guião2 % ./3         
pai = 6359 , filho = 6361 
pai = 6359 , filho = 6362 
pai = 6359 , filho = 6363 
pai = 6359 , filho = 6364 
pai = 6359 , filho = 6365 
pai = 6359 , filho = 6366 
pai = 6359 , filho = 6367 
pai = 6359 , filho = 6368 
pai = 6359 , filho = 6369 
pai = 6359 , filho = 6370 
*/

/*

int main (int argc, char *argv[]) {                         // VERSÃO CONCORRENTE //

    pid_t pid;
    int status;

    for (int i=0; i<10; i++){
	    pid = wait(&status);
        if(WIFEXITED(status)) {
            printf("pid = %d , exit = %d \n", pid, WEXITSTATUS(status));
        }
    }    
    
    puts("Out for");    
    return 0;                      // aqui temos um ciclo de criação de processos e um ciclo de espera de ciclo de processos
}

/*

int main (int argc, char *argv[]) {                         // VERSÃO CONCORRENTE //

    pid_t pid;
    int status;

    for (int i=0; i<10; i++){
	    pid = fork();
        if(pid==0) {
            printf("Filho= %d , Pid Filho , Pid Pai = %d \n", i, getpid(), getppid());
        }

        pid = wait(&status);
        if(WIFEXITED(status)) {
            printf("exit = %d \n", WEXITSTATUS(status));
        }
    }    
    
    puts("Out for");    
    return 0;                      // aqui temos um ciclo de criação de processos e um ciclo de espera de ciclo de processos
}

*/
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>

#include <sys/stat.h>


int main (int argc, char *argv[]) {

    pid_t pid;
    int status;

    // Executar sequencialmente
    for (int i=0; i<10; i++){
	    pid = fork();
        if(pid == 0) {
            printf("Pai = %d , Filho = %d \n", getppid(), getpid());
            exit(i);        // Para sair do correto
        }
    
        int status;                                     // Para termos a espera entre cada um elemento do ciclo
        pid_t pid = wait(&status);
        if(WIFEXITED(status)) {
            printf("_exit: %d \n", WEXITSTATUS(status));
        }
    }    

    //waitpid(pid,&status, WCONTINUED);

    puts("Out for");
    return 0;               //não é necessário, mas por norma, quando um porgrama corre bem, devolve-se 0;
}

/*
(base) paulinhordc@MacBook-Pro-de-Paulo Guião2 % gcc 3.c -o 3
paulinhordc@MBP-de-Paulo Guião2 % ./3
Pai = 3214 , Filho = 3216 
_exit: 0 
Pai = 3214 , Filho = 3217 
_exit: 1 
Pai = 3214 , Filho = 3218 
_exit: 2 
Pai = 3214 , Filho = 3219 
_exit: 3 
Pai = 3214 , Filho = 3220 
_exit: 4 
Pai = 3214 , Filho = 3221 
_exit: 5 
Pai = 3214 , Filho = 3222 
_exit: 6 
Pai = 3214 , Filho = 3223 
_exit: 7 
Pai = 3214 , Filho = 3224 
_exit: 8 
Pai = 3214 , Filho = 3225 
_exit: 9 
Out for
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

*/

/*

int main (int argc, char *argv[]) {                         

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
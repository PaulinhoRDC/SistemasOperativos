/*
2. Implemente um programa semelhante ao anterior que execute o mesmo comando mas agora no contexto
de um processo filho.
*/

#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h> 
#include <sys/wait.h>

int main(int argc, char* argv[]){

    pid_t pid;

    pid = fork();
    if (pid == 0){
        execlp("ls", "ls", "-l",NULL);  
        _exit(0);
    }
    
    int status;
    pid = wait(&status);
    if(WIFEXITED(status)) {printf("\n_exit: %d \n", WEXITSTATUS(status)); }

    return 1;
}
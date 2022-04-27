/*

5. Escreva um programa que emule o funcionamento do interpretador de comandos na execução encadeada
de grep -v ˆ# /etc/passwd | cut -f7 -d: | uniq | wc -l.

*/
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main (int args, char * argv[]){
    int comands = 4;
    int pipe_fd[3][2];

    //criar pipe
    if (pipe(pipe_fd[0]) < 0){
        perror("pipe");
        exit(1);
    }


    //criar processo grep
    if (fork() == 0){
        
        close (pipe_fd[0][0]);

        dup2(pipe_fd[0][1],1);
        close(pipe_fd[0][1]);

        //1 -> pipe[0][1]

        execlp ("grep","grep","-v","^#","/etc/passwd", NULL);

        _exit(1);
    }

    close(pipe_fd[0][1]);

    //criar pipe 1
    if (pipe(pipe_fd[1]) < 0){
        perror("pipe[1]");
        exit(1);
    }

    //criar processo "cut"

    if (fork() == 0){
        //abertos
        //pipe [0][0]
        //pipe [1][0]
        //pipe [0][1]

        close(pipe_fd[1][0]);

        dup2(pipe_fd[0][0], 0);
        close(pipe_fd[0][0]);

        dup2(pipe_fd[1][1], 1);
        close(pipe_fd[1][1]);

        execlp("cut","cut","-f7","-d:",NULL);

        _exit(1);
    }
    
    close(pipe_fd[0][0]);
    close(pipe_fd[1][1]);


    
    //criar pipe 2
    if (pipe(pipe_fd[2]) < 0){
        perror("pipe");
        exit(1);
    }

    if (fork() == 0){
        //abertos
        //pipe[1][0]
        //pipe[2][0]
        //pipe[2][1]

        close(pipe_fd[2][0]);

        dup2(pipe_fd[1][0],0);
        close(pipe_fd[1][0]);

        dup2(pipe_fd[2][1],1);
        close(pipe_fd[2][1]);

        execlp("uniq","uniq",NULL);

        _exit(1);
    }

    close (pipe_fd[1][0]);
    close (pipe_fd[2][1]);

    if (fork() == 0){
        //pipe [2][0]
        
        dup2(pipe_fd[2][0],0);
        close(pipe_fd[2][0]);

        execlp("wc","wc","-l",NULL);

        _exit(1);

    }

    close (pipe_fd[2][0]);

    for (int i = 0; i < comands; i++){
        wait (NULL);
        //verificar estado etc
    }

    return 0;
}
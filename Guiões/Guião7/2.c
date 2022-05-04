/*
2. Considere o programa grep, que procura ocorrências de uma dada palavra num dado ficheiro. 
O código de saída deste programa é 0 caso encontre ocorrências no ficheiro.
                grep "palavra" ficheiro.txt
Implemente o programa multigrep com a mesma funcionalidade, tirando partido do programa grep,
mas que permite ter vários processos a procurar uma dada palavra em vários ficheiros concorrentemente.
Certifique-se de que todos os processos terminam assim que um deles encontre a palavra.
*/

#include <signal.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
typedef void (*sighandler_t)(int);

int main (int argc, char *argv[]) {

    if (argc < 3) {
        puts("Usage: multigrep <palavra> <file> ...");
        return 5;
    }

    int files_count = argc - 2;
    char **files = argv + 2;

    int pids[files_count];

    for (int i = 0; i < files_count; i++) {
        pid_t pid = -1;
        if (!(pid = fork())) {
            printf("grep #%d com pid %d no ficheiro \"%s\"\n", i, getpid(), files[i]);

            if (execlp("grep", "grep", argv[1], files[i], NULL) < 0) {
                perror("Exec grep error");
                exit(10);
            }
        }
        pids[i] = pid;
    }

    int status = 0; 
    int found = 0;
    int pid;

    while (!found && (pid = wait(&status)) > 0) {
        if(WIFEXITED(status)) {
            switch(WEXITSTATUS(status)) {
                case 0: 
                    found = 1;
                    printf("grep com pid %d encontrou a palavra\n", pid);
                    break;
                default:
                    printf("grep %d não encontrou a palavra.\n", pid);
                    break;
            }
        }
    }

    if (!found) return 1;
    
    for (int i = 0; i < files_count; i++) {
        printf("A tentar terminar grep com pid: %d\n", pids[i]);
        if (pids[i] > 0) {
            kill(pids[i], SIGKILL);

            if (waitpid(pids[i], &status, 0) > 0) {
                if (WIFEXITED(status)) {
                printf("Processo em grep %d acabou.\n", pids[i]);
                }
                else {
                    printf("grep %d terminado.\n", pids[i]);
                }
            }
        }
    }
    return 0;
}


/*

paulinhordc@MacBook-Pro-de-Paulo Guião7 % ./2 "gato" 2.txt 
grep #0 com pid 21799 no ficheiro "2.txt"
O gato roeu a rolha da garrafa do rei da russia.
grep com pid 21799 encontrou a palavra
A tentar terminar grep com pid: 21799
paulinhordc@MacBook-Pro-de-Paulo Guião7 % ./2 "rato" 2.txt
grep #0 com pid 21806 no ficheiro "2.txt"
grep 21806 não encontrou a palavra.

*/
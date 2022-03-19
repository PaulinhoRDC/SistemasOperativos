/*
6. A partir do cen´ario descrito no exerc´ıcio anterior, pretende-se que imprima por ordem crescente os
n´umeros de linha onde existem ocorrˆencias do n´umero.
*/

#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h> 
#include <sys/wait.h>

#define linhas 5
#define col 10

int matrix[linhas][col];

void printmatrix() {
    for(int i = 0; i < linhas; i++) {
        for(int j = 0; j < col; j++) {
            printf("%d", matrix[i][j]);
        }
        printf("\n");
    }
}

int main() {
    pid_t pid;
    
    int num = 1; //numero a procurar
    int ocorr = 0;
    int arrayPids[linhas];


    // 
    for(int i = 0; i < linhas; i++) {
        for(int j = 0; j < col; j++) {
            matrix[i][j] = 0;
        }
    }  
    matrix[0][9] = 1;
    matrix[1][5] = 1;
    matrix[4][0] = 1;
    
    /*
    // criar matrix aleatória
    for(int i = 0; i < linhas; i++) {
        for(int j = 0; j < col; j++) {
            matrix[i][j] = rand()%col;
        }
    }
    */
    
    // Executar em concorrencia
    for(int i=0; i<linhas; i++) {
        pid = fork();                                                   // cria-se um filho por linha

        if(pid == 0) {
            arrayPids[i] = getppid();                                    // guardar pid do filho criado

            //percorrer as colunas da matrix até encontrar o numero
            for(int j=0;j<col;j++) {
                if(matrix[i][j] == num) {
                    _exit(1);
                }
            }
            _exit(0);
        }
    }
    
    //WIFEXITED(status) : returns true if the child terminated normally.
    //WEXITSTATUS(status) : returns the exit status of the child. This macro should be employed only if WIFEXITED returned true.

    for(int i=0; i<linhas; i++) {
        int status;
        pid_t pid = wait(&status);
        
        if(WIFEXITED(status)) {
            printf("_exit: %d \n", WEXITSTATUS(status));
            if(WEXITSTATUS(status) == 1) ocorr++;
        }
    }
    
    printf("\n");

    printf("Ocorr: %d \n",ocorr);
    printf("\n");

    printmatrix();
    printf("\n");

    for(int i=0; i<linhas; i++){
        printf("%d \n", arrayPids[i]);
    }



    return 0;
} 
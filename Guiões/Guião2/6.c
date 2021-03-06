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
        arrayPids[i] = pid;

        if(pid == 0) {
            // arrayPids[i] = getppid();                                    // guardar pid do filho criado

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
            if(WEXITSTATUS(status) == 1){
                ocorr++;
                for(int j=0; j<linhas; j++){                                                 // for(int j=0; arrayPids[j] != pid; j++)
                    if(arrayPids[j] == pid) { printf ("Linha: %d , Pid: %d  \n", j, pid); }
                }
            }
        }
    }
    
    printf("\n");

    printf("Ocorr: %d \n",ocorr);
    printf("\n");

    printmatrix();
    printf("\n");

    return 0;
} 

/*
podiamos fazer, ao invés de usar printf: 
                                            for(int i=0; i!=N; i++) {
                                                char str[256];
                                                snprintf (str, sizeof(str), "%d", i);
                                            }
*/


/**
 *  (base) paulinhordc@MBP-de-Paulo Guião2 % gcc 6.c -o 6
    (base) paulinhordc@MBP-de-Paulo Guião2 % ./6         
    Linha: 1 , Pid: 1255  
    Linha: 0 , Pid: 1254  
    Linha: 4 , Pid: 1258  

    Ocorr: 3 

    0000000001
    0000010000
    0000000000
    0000000000
    1000000000
 * 
 */
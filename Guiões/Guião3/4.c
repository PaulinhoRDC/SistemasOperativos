/*
4. Implemente uma versão simplificada da função system(). Ao contrário da função original, não tente
suportar qualquer tipo de redireccionamento, ou composição/encadeamento de programas executáveis.
O único argumento deverá ser uma string que especifica um programa executável e uma eventual lista de
argumentos. Procure que o comportamento e valor de retorno da sua função sejam compatíveis com a
original.
*/

#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h> 
#include <sys/wait.h>


int mySystem(char *comand) {                                                    // VERIFICAR AULA DO STOR ONLINE (DIA 25/03/2022)

    char *buf[100];

    //copia a string comand para uma string auxiliar
    char *aux = strdup(comand);

    int i=0;

    // parte a string aux em vários tokens com o delimitador " " (espaço)
    // "ls -l" fica -> "ls \0 -l \0"
    char *token = strtok(aux, " ");

    //buf[0] toma o valor da primeira componente, neste caso ls, que vai ser o primeiro argumento do execvp
    //printf("Debug: %s \n", buf[0]);
    buf[i] = token;

    //Incrementamos o i para copiar o resto dos argumentos
    i++;

    //Copiar o resto dos argumentos
    while(buf[i]!=NULL) {
        buf[i]=strtok(NULL, " ");
        i++;
    }
    
    pid_t pid;
    pid = fork();

    if(pid==0) {
        execvp(buf[0],buf);
        _exit(1);
    }
    int status;
    wait(&status);

    return 0;
}



int main() {
    
    mySystem("ls -l");


}
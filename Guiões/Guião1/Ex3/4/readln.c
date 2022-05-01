#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>

ssize_t readln(int fd, char* line, size_t size){

    int n, nb=0;                    // VAMOS EFETUAR LEITURA BYTE A BYTE
    
    while (nb < size && (n= read(fd, line + nb, 1)) > 0  && line[nb] != '\n' ) {    
        nb++;
    }        

    if (n == -1)
        return -1;

    return nb > 0 && line[nb] == '\n' ? nb + 1 : nb;
}

int main() {
    char buffer[1024];        //PODEMOS IR ALTERANDO O VALOR DO BUFFER         //USANDO STATIC, TEMOS UMA MELHOR IMPLEMENTAÇÃO

    printf ("%ld \n", readln (0, buffer, sizeof(buffer)));
    return 0;
}

/*

(base) paulinhordc@MBP-de-Paulo Guião1 % gcc readln.c -o readln
(base) paulinhordc@MBP-de-Paulo Guião1 % ./readln
ola
4 

*/

/*

Tendo dois módulos, podemos aceder a variáveis de fora: 
                                                                f.c             g.c
                                                              
                                                               int x;          extern int x;

                                                >> gcc -c f.c   -> gera f.o
                                                >> nm f.o

Se em f.c, x fosse declarado como : static int x;   
                                                    já não seria fácil usar x fora do módulo f;
                                            

ssite_t readln (...)

    char buffer[80];                // sempre que a função retornar, o buffer foi-se e perde-se

    static char buffer[80];         // o que sobrar do primeiro retorno, é preservável no restante  
                                       (ou seja, só se inicializa uma vez, como as variáveis globais)



*/
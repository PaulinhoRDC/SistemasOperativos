/*
6.  Considere uma estrutura (struct) com dados de uma pessoa (nome, idade, ...) 
e um ficheiro binário que contém registos organizados segundo esta estrutura.

Não assuma que o ficheiro cabe todo em mem ória.

Escreva um programa que, consoante a opção, permita:

    -i -  Acrescentar pessoas a um ficheiro de dados (binário – a idade  é um inteiro).
    -u -  Atualizar a idade de uma determinada pessoa no ficheiro de dados.
    
Exemplos:
$ pessoas  -i "José Mourinho" 55
$ pessoas  -u "José Mourinho" 56 

Meça o tempo que demora a inserir 1.000.000 de pessoas (nomes e idades gerados por si).   
Observa alguma degradação de desempenho à medida que o ficheiro cresce?

*/

#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>

#include "person.h"


int main (int argc, char *argv[]) {
    Pessoa p;

    if (argc < 5) {
        printf("Erro: Nao foram inseridos argumentos suficientes na linha de comandos.\n");
        return 0;
    }

    if(strcmp(argv[2],"-i") == 0) {
        int res;
        
        strcpy(p.nome,argv[3]);
        p.idade = atoi(argv[4]);

        int fd = open("pessoas.txt", O_CREAT | O_APPEND | O_WRONLY, 0666);
        if(fd == -1) perror("Error no open");

        res = write(fd, &p, sizeof(p));      //temos de passar obrigatoriamente, o apontador de p, no segundo parâmetro
        
        int pos = lseek(fd, -sizeof(Pessoa), SEEK_CUR);                         // alínea 7

        /*
        //index of most recent entry (Nao faço ideia como é que isto funciona)
        struct stat st;
        fstat(fd,&st);
        off_t filesize = st.st_size;
        pos = (int)filesize / sizeof(Pessoa);

        */

        if(res >= 0) {
            printf("Inserido ");
            printf("Na posição: %d", pos);                                                                                             // alínea 7
        
        }
        else{
            perror("Erro no write");
        }        

        close(fd);
    }

    if(strcmp(argv[2],"-u") == 0) {
        int res;
        int fd = open("pessoas.txt", O_WRONLY | O_RDONLY, 0666);
        if(fd == -1) perror("Error no open");

        while(read(fd,&p,sizeof(Pessoa)) > 0) {

            if(strcmp(p.nome,argv[3]) == 0) {

                lseek(fd,-sizeof(Pessoa),SEEK_CUR);

                p.idade = atoi(argv[4]);

                res = write(fd,&p,sizeof(Pessoa));

                if(res >= 0) {
                    printf("Inserido");
                }
                else {
                    perror("Erro no write");
                }

                close(fd);
            }
        }
 
    }

    if(strcmp(argv[2],"-o") == 0) {

        int res;
        int fd = open("pessoas.txt", O_WRONLY | O_RDONLY | O_CREAT, 0666);
        if(fd == -1) perror("Error no open");

        int posicao = atoi(argv[3]);

        // encontrar a posicao

        // lseek(fd,sizeof(Pessoa)*posicao,SEEK_SET);
        lseek(fd,sizeof(struct pessoa) * ( atoi(argv[3]) -1),SEEK_SET);

        int fde = read(fd,&p,sizeof(p));
        if(fde < 0) perror("Error no read");

        p.idade = atoi(argv[4]);

        // lseek(fd,sizeof(p),SEEK_CUR);
        lseek(fd, sizeof(struct pessoa) * ( atoi(argv[3]) -1),SEEK_SET);

        res = write(fd,&p,sizeof(p));
        if(res >= 0) {
            printf("Inserido");
            
        }
        else{
            perror("Erro no write");
        }
        close(fd); 
        }

        if(strcmp(argv[2],"-h") == 0) {
            ssize_t res;
            char idString[20];

            int fd = open("pessoas.txt", O_RDONLY);

            while((res = read(fd,&p,sizeof(Pessoa))) > 0) {
                printf("%s - %d \n", p.nome,p.idade);
            }
            close(fd);
        }

} 




/*

off_t lseek (int fd, off_t off, int whence);

                   | If whence is SEEK_SET, the offset is set to offset bytes.

                   | If whence is SEEK_CUR, the offset is set to its current location plus offset bytes.

                   | If whence is SEEK_END, the offset is set to the size of the file plus offset bytes.

lseek retorna sempre o deslocamento realizado desde o início do ficheiro.

*/


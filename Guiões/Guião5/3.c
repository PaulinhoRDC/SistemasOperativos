/*

3. Escreva um programa que execute o comando wc num processo filho. O processo pai deve enviar ao
filho através de um pipe anónimo uma sequência de linhas de texto introduzidas pelo utilizador no seu
standard input. Recorra à técnica de redireccionamento estudada no guião anterior de modo a associar
o standard input do processo filho ao descritor de leitura do pipe anónimo criado pelo pai. Recorde a
necessidade de fechar o(s) descritor(es) de escrita no pipe de modo a verificar-se a situação de end of file.


//BONECADA//

    pai <- ecrã                                 
     |
     | 1
     -
     | 0
     |
     filho <-                                           TLDF                            TGDF
                                                        0(input)                        ECRÃ
                                                        1(output)                      TECLADO
                                                        2(error)                       TECLADO
                                                        PD[0] = 3
                                                        PD[1] = 4

    1) criar pipe anónimo                                -> pipe
    2) criar filho                                       -> fork                  (herda exatamente os mesmo descritores)
    3) redirecionar stdin para canal de leitura no filho -> dup2    (0 -> pd[0])
    3.5) fechar descritores desnecessários               -> pd[0] no pai & pd[1] no filho
    4) executar wc no filho                              -> execlp

*/

#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {

    int p[2];
    char buffer[1024];
    int status;

    if(pipe(p) == -1) {         /* pai  erro */
        perror("Erro no pipe");
        return -1;
    }

    pid_t pid;
    pid = fork();

    if(pid==0) {            /* filho */
        dup2(p[0],0);

        // fechar o que nao é necessário
        close(p[0]);
        close(p[1]);

        execlp("wc","wc",NULL);

        _exit(0);
    }

    /* pai sucesso */
    close(p[0]);

    int n;
    while((n = read(0,buffer,sizeof(buffer))) > 0) {
        write(p[1],buffer,n);
    }


    close(p[1]);
    wait(&status);
    printf("[Pai] Out of wait \n");

    return 0;
}

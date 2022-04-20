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

int main(){

    char buffer[512];
    int nb;
    int pd[2];
    pipe(pd);

    switch(fork()) {
        case 0: /* filho */

                dup2(pd[0], 0);
                
                //fechar canais desnecessários
                close(pd[0]);
                close(pd[1]);

                execlp("wc", "wc", "-l", NULL);
                perror("wc");
                _exit(1);
        case -1: /* pai  erro */
                perror("fork");
                return 1; /*EXIT_FAILURE */
        default: /* pai sucesso */
                close(pd[0]);
                while((nb = read(0, buffer, sizeof(buffer)) > 0)){
                    write(pd[1], buffer, nb);
                }
                close(pd[1]);


    }
    return 0;  /* EXIT_SUCCESS => #include <stdlib.h>  */
}
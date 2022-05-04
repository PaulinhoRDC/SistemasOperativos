/*
1. Usando SIGINT, SIGQUIT e SIGALRM, escreva um programa que vá contando o tempo em segundos
desde que comecçou. 
Se, entretanto, o utilizador carregar em Ctrl+C, o programa deverá imprimir o tempo passado. 
Se carregar em Ctrl+\ o programa deverá indicar quantas vezes o utilizador carregou em Ctrl+C e terminar de seguida.
*/

#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int ctrl_c_counter = 0;
int seconds = 0;

void sigint_handler (int signum) {
    printf("sigint received code %d\n",signum);
    //tempo passado
    printf("execution time: %d\n",seconds);
    ctrl_c_counter ++;
}

void sigquit_handler (int signum) {
    printf("sigquit received code %d\n",signum);
    printf("ctrl + c counter: %d",ctrl_c_counter);
    exit(0);
}

void sigalarm_handler (int signum){
    printf("alarm signal received code: %d\n",signum);
    seconds ++; 
    alarm(1);                                           // Para pedir outro SIGALARM, para continuar a contar os segundos
                                                        // se não, contava apenas 1 segundo;
}

/*                                  Podiamos pôr em case's
void handler(int signal){
    switch(signal){
        case SIGALARM:
            printf("alarm signal received code: %d\n",signum);
            seconds ++; 
            alarm(1);
        case SIGINT:
            printf("sigint received code %d\n",signum);
             printf("execution time: %d\n",seconds);
            ctrl_c_counter ++;
        case SIGQUIT:
            printf("sigquit received code %d\n",signum);
            printf("ctrl + c counter: %d",ctrl_c_counter);
            exit(0);
    }
}
*/

//sigint é crtl + c
//sigquit é crtl + /

int main (int argc, char * argv[]){
    if (signal(SIGINT, sigint_handler) == SIG_ERR){
        perror("signal sigint");
        exit(1);
    }

    if (signal(SIGQUIT, sigquit_handler) == SIG_ERR){
        perror("signal sigkill");
        exit(1);
    }

    if (signal(SIGALRM,sigalarm_handler) == SIG_ERR){
        perror("signal sigalrm");
        exit(1);
    }
    
    alarm(1);
    while(1){
        //alarm(1); nao podemos meter aqui senao pode reniciar devido ao pause
        //aceitar qualquer sinal e assim nunca mais acaba e nao conta tempo
        //por isso temos de colocar o sigalarm a contar denovo alarm(1)s
        //printf("alarm setup \n");
        pause();       //precisamos senao consome demasiado cpu
        //sleep(1); e seconds++; nao funciona pois é interrompido
        printf("interrupted \n");
    }

    return 0;
}
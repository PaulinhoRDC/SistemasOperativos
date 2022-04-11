/*

                                        PIPES ANÓNIMOS

- Comunicação entre processos relacionados (pai/filho, entre filhos do mesmo pai, ...)

- Buffer em memória (array de bytes em memória...) , ou seja, espaço limitado. Que vai ser escrito e lido!
- Chamamos de produtores e consumidores, i.e., quem consome está a ler bytes do pipe e quem produz está a escrever. 

- Num pipe, os pypes são consumidos, i.e., se lermos 3 bytes, estes são "consumidos" e já não estão lá, 
DIFERENTE DE UM READ DE UM FICHEIRO NORMAL.

- Num read de um pipe, se não houver bytes a ler, este é bloqueado, em vez, de devolver 0.
DIFERENTE DE UM READ DE UM FICHEIRO NORMAL.

- Se um buffer encher, o pipe é bloqueado pois não da para dar write.
DIFERENTE DE UM READ DE UM FICHEIRO NORMAL.

- Não podemos fazer lseek's em pipes.

- FIFO, se eu sou um produtor e escrevo a mensagem "Olá" para um pipe, ao lermos o pipe, vamos obter esta mensagem.
FIRST IN FIRST OUT

- CHAMADAS AO SISTEMA:
                                int pipe (int fildes[2])
                                                            - fildes[1] aloca o descritor para ler do pipe
                                                            - fildes[2] aloca o descritor para escrever no pipe

- EXEMPLO 1:                        (EX.1)
    int filho2pai(){

        int p[2];
        char line[] = "linha1\n";
        char buffer[20];
        int res;
        int status;

        if(pipe(p) == -1){
            perror("pipe");
            return -1;
        }

        //p[0] -> extremo leitura
        //p[1] -> extremo escrita

        getchar();   
    }        

    >> lsof -c ex1      
        VER OS DESCRITORES QUE ESTÃO ABERTOS NESTE MOMENTO       

                                            

    --------------------------------- 

- EXEMPLO 2:
    int filho2pai(){

        int p[2];
        char line[] = "linha1\n";
        char buffer[20];
        int res;
        int status;

        if(pipe(p) == -1){
            perror("pipe");
            return -1;
        }

        switch (fork(){
            case -1:
                perror("fork");
                return -1;
            case 0:
                //filho
                //fechar o descritor de leitura no filho
                close(p[0]);
                //sleep(5);
                write(p[1], &line, sizeof(line));
                printf("[FILHO]: wrote line to pipe \n");
                close(p[1]);                                    // MANDA UMA LINHA, E FAÇO CLOSE
                _exit(0);
            default: 
                //pai
                //fechar o descritor de escita no pai
                close(p[0]);
                //aqui o res é importante para saber quanto lemos realm realmente
                res = read(p[0], &buffer, sizeof(buffer));
                printf("[PAI]: read %s  from pipe \n", bufffer);
                close(p[0]);

                //Porque o wait só aqui?
                wait(&status);
        }
        return 0;
    }   

    >> gcc ex1.c -o ex1
    >> ./ex1

    [FILHO]: wrote line to pipe
    [PAI]: read linha1
     from pipe


   --------------------------------- 

- EXEMPLO 3:
    int pai2filho(){

        int p[2];
        char line[] = "linha1";
        char buffer[20];
        int res;
        int status;

        if(pipe(p) == -1){
            perror("pipe");
            return -1;
        }

        switch (fork(){
            case -1:
                perror("fork");
                return -1;
            case 0:
                //filho
                //fechar o descritor de escrita no filho
                close(p[1]);
                //aqui o res é importante para saber quanto lemos realm realmente
                res = read(p[0], &buffer, sizeof(buffer));
                printf("[FILHO]: read %s from pipe res %d \n", buffer, res);
                close(p[0]);                                    
                _exit(0);
            default: 
                //pai
                //fechar o descritor de leitura no pai
                close(p[0]);
                //sleep(5);
                write(p[1], &line, strlen(line));
                printf("[PAI]: wrote line to pipe \n");
                close(p[1]);

                //Porque o wait só aqui?
                wait(&status);
        }
        return 0;
    }   

    >> gcc ex1.c -o ex1
    >> ./ex1

    [PAI]: wrote line to pipe
    [FILHO]: read linha1 from pipe res 6

    --------------------------------- 

- EXEMPLO 3:
    int pai2filho(){

        int p[2];
        char line[] = "linha1";
        char buffer[20];
        int res;
        int status;

        if(pipe(p) == -1){
            perror("pipe");
            return -1;
        }

        switch (fork(){
            case -1:
                perror("fork");
                return -1;
            case 0:
                //filho
                //fechar o descritor de escrita no filho
                close(p[1]);
                //aqui o res é importante para saber quanto lemos realm realmente
                res = read(p[0], &buffer, sizeof(buffer));
                printf("[FILHO]: read %s from pipe res %d \n", buffer, res);
                close(p[0]);                                    
                _exit(0);
            default: 

                //E se o wait tivesse logo aseguir ao default?
                wait(&status);

                //pai
                //fechar o descritor de leitura no pai
                close(p[0]);
                //sleep(5);
                write(p[1], &line, strlen(line));
                printf("[PAI]: wrote line to pipe \n");
                close(p[1]);                
        }
        return 0;
    }

    Se o wait for colocado ali:
        filho fará read e bloqueará no read, pois o buffer ainda não tem lá nada.
        em seguida, o pai vai esperar que o filho termine.
        mas o filho está à espera, enquanto o pai também.
        LOGO, ambos ficarão à espera para todo o sempre.
        !DEADLOCK!


    --------------------------------- 

                LEITURAS:

    read()- TEM DADOS?
        - SIM: lê dados, return > 0;
        - NÃO: TODOS EXTREMOS DE ESCRITA FECHADOS? 
            - NÃO: bloqueia;                //podem haver processos a tentar escrever para o pipe
            - SIM: return 0 (End Of File)   //já todos os extremos de escrita associados a este pipe, foram fechados


                ESCRITAS:
        
    write()- TODOS EXTREMOS DE LEITURA FECHADOS?
        - SIM: SIGPIPE (mata pipe / mata escritor)
        - NÃO: HÁ ESPAÇO?
            - NÃO: bloqueia;
            - SIM: escreve. return > 0;

    --------------------------------- 
   
Ex. 2) 

int pai2filho(){

        int p[2];
        char * lines[] = "linha1", linha2", linha3", linha4", linha5" ;
        char buf;
        int num_lines = 5;;
        int status;

        if(pipe(p) == -1){
            perror("pipe");
            return -1;
        }

        switch (fork(){
            case -1:
                perror("fork");
                return -1;
            case 0:
                //filho
                //fechar extremo de de escrita no filho (comentar para mostrar que o filho não tem ...)
                close(p[1]);    // TEMOS DE TER ESTE EXTREMO DE ESCRITA FECHADO, PORQUE SE NÃO TEMOS DEADLOCK
                while ((res = read(p[0], buf, 1)) > 0){                    //ENQUANTO HÁ DESCRITORES DE ESCRITA ABERTOS    // LER BYTE A BYTE  (Podemos mudar para testar)
                    buf[res] = '\0' ;
                    printf("[FILHO]: read %s from pipe\n", buf);
                }
                printf("[FILHO]: out of while \n");
                close(p[0]);                                    
                _exit(0);
            default: 
                //pai
                //fechar o descritor de leitura no pai
                close(p[0]);
                for (int i = 0; i < num_lines; i++){
                    write(p[1], lines[i], strlen(lines[i]));
                    printf("[PAI]: wrote %s line to pipe \n", lines[i]);
                    //sleep(10);
                }
                //Enquanto pai não fechar o filho fica bloqueado...
                //sleep(10);
                //fechar extremo de escrita no pai
                close(p[1]); 
                wait(&status);
                printf("[PAI]: out of wait\n");              
        }
        return 0;
    }

    --------------------------------- 




*/
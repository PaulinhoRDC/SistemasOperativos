/*
Objectivos
    Familiarizar-se e utilizar as chamadas ao sistema relativas `a comunicac¸ ˜ao entre processos por pipes com nome.
Chamadas ao sistema
    #include <sys/types.h>
    #include <sys/stat.h>
    int mkfifo(const char *pathname, mode_t mode);

--------------------

Vemos quais as listagens na diretoria em que estamos:
 
    paulinhordc@MacBook-Pro-de-Paulo Guião6 % ls -l
    total 96
    -rw-r--r--@ 1 paulinhordc  staff  45647 27 Abr 16:29 guiao-06.pdf

Se depois invocarmos >>mkfifo exemplo :

    paulinhordc@MacBook-Pro-de-Paulo Guião6 % mkfifo [-n 0666] exemplo                                  // [ ] -> optional
    paulinhordc@MacBook-Pro-de-Paulo Guião6 % ls -l
    total 96
    -rw-r--r--  1 paulinhordc  staff      0 27 Abr 16:31 ExplicaçõesProf.c
    prw-r--r--  1 paulinhordc  staff      0 27 Abr 16:31 exemplo
    -rw-r--r--@ 1 paulinhordc  staff  45647 27 Abr 16:29 guiao-06.pdf

No primeiro caracter, - significa ficheiros , d significa diretorias , p significa pipes ,(...)

*/
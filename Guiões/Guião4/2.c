/*
2. Modifique o programa anterior de modo a que, depois de realizar os redireccionamentos, seja criado um
novo processo que realize operações de leitura e escrita. Observe o conteúdo dos ficheiros. Repare que o
processo filho “nasce” com as mesmas associações de descritores de ficheiros do processo pai.
*/

#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h> 
#include <sys/wait.h>

int main(){

    pid_t pid;

    int fd = open("/etc/passwd", O_RDONLY);
    dup2(fd,0);
    close(fd); 

    int fd2 = open("saida.txt",O_CREAT|O_WRONLY|O_TRUNC, 0666);
    close(1);
    dup(fd2);
    close(fd2);

    int fd3 = open("erros.txt",O_CREAT|O_WRONLY|O_TRUNC, 0666);
    dup2(fd3,2);
    close(fd3);
    
    pid = fork();
	if(pid==0){		/*filho*/
        printf("Terminei filho");                             // vai escrever no saida.txt (que é o que está no standard output)
		exit(0);
	}
    
    return 0;
    
}
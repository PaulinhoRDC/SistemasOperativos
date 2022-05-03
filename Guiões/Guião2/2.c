#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>

#include <sys/stat.h>


int main (int argc, char *argv[]) {
    
    pid_t pid;
    puts("ola");               // colocar em comentário
	pid = fork();
	if(pid==0){		/*filho*/

		printf("filho: pid = %d , ppid = %d \n", getpid(), getppid());
		exit(0);
	}

	sleep(1); // isto para o processo filho ter tempo de acabar antes do pai; //

	printf ("pai: pid = %d , ppid = %d , filho = %d", getpid(), getppid(), pid);
	return 0;
}

/*
paulinhordc@MBP-de-Paulo Guião2 % gcc 2.c -o 2
paulinhordc@MBP-de-Paulo Guião2 % ./2         
ola
filho: pid = 3081 , ppid = 3079 
pai: pid = 3079 , ppid = 1983 , filho = 3081
*/
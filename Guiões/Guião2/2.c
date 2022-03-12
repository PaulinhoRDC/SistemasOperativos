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
(base) paulinhordc@MacBook-Pro-de-Paulo Guião1 % gcc 2.c -o 2
(base) paulinhordc@MBP-de-Paulo Guião1 % ./2
*/
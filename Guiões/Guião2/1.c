#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>

#include <sys/stat.h>


int main (int argc, char *argv[]) {

pid_t getpid();  
	// devolve, o pid do processo do mesmo;

pid_t getppid();
	// devolve, o pid do processo pai;

printf ("pid = %d , ppid = %d", getpid(), getppid());

}
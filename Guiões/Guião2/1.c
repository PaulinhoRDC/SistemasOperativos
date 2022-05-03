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

/*
paulinhordc@MBP-de-Paulo Guião2 % gcc 1.c -o 1
paulinhordc@MBP-de-Paulo Guião2 % ./1
pid = 2807 , ppid = 1983%                                                                                                                                               
paulinhordc@MBP-de-Paulo Guião2 % ps
  PID TTY           TIME CMD
 1983 ttys000    0:00.32 /bin/zsh -l

*/
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>

#include "readln.h"

#define BUFSIZE 1024

int main(int argc, char* args[]) {

    int n, nl = 1;
    char buffer[BUFSIZE+1] , line [BUFSIZE+16];

    while((n = readln(0,buffer, BUFSIZE)) > 0) {

        buffer[n] = '\0';
        sprintf (line, "%8d      %s", nl, buffer);
        write(1,line,strlen(line));
        nl++;
    }

    return 0;  /* EXIT_SUCCESS */

} 

/*

(base) paulinhordc@MBP-de-Paulo Guião1 % gcc -Wall -c mynl.c
(base) paulinhordc@MBP-de-Paulo Guião1 % nm mynl.o
                 U ___sprintf_chk
                 U ___stack_chk_fail
                 U ___stack_chk_guard
0000000000000000 T _main
                 U _readln
                 U _write

(base) paulinhordc@MBP-de-Paulo Guião1 % gcc -Wall -c readln.c 
(base) paulinhordc@MBP-de-Paulo Guião1 % nm readln.o
                 U ___stack_chk_fail
                 U ___stack_chk_guard
00000000000000f0 T _main
                 U _printf
                 U _read
0000000000000000 T _readln

(base) paulinhordc@MBP-de-Paulo Guião1 % gcc mynl.o readln.o -o mynl
duplicate symbol '_main' in:
    mynl.o
    readln.o
ld: 1 duplicate symbol for architecture x86_64
clang: error: linker command failed with exit code 1 (use -v to see invocation)

*/

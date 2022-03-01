#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>     // para utilizar o perror

#define BUFSIZE 1

int main(int argc, char* argv[]) {    
    int ofd, dfd, n;
    char buffer[BUFSIZE];

    ofd = open(argv[1], O_RDONLY);      
    if (ofd == -1){
        perror(argv[1]);
        return 1; /* EXIT_FAILURE */
    }

    dfd = open(argv[2], O_CREAT|O_TRUNC|O_WRONLY, 0666);
    if(dfd == -1){
        perror(argv[2]);
        return 1; /* EXIT_FAILURE */
    }

    while ((n = read (ofd, buffer, sizeof(buffer))) > 0){
        write(dfd, buffer, n);
    }

    close(ofd);
    close(dfd);

    return 0;

    
} 

// gcc -o nomeguardar nomeficheiro
// ./nomeficheiro
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include "backup.h"

int main(int argc, char *argv[]) {
    int pipefd[2];
    
    if (pipe(pipefd) == -1) {
        perror("Error al crear el pipe");
        exit(EXIT_FAILURE);
    }
    
    pid_t pid = fork();
    
    if (pid == -1) {
        perror("Error al hacer fork");
        exit(EXIT_FAILURE);
    }
    
    if (pid == 0) {
        // Proceso hijo
        close(pipefd[1]); // Cierra escritura
        proceso_hijo(pipefd, argv[1], argv[2]);
        close(pipefd[0]); // Cierra lectura
    } else {
        // Proceso padre
        close(pipefd[0]); // Cierra lectura
        proceso_padre(argv[1], argv[2], pipefd);
        close(pipefd[1]); // Cierra escritura
        
        wait(NULL); // Espera al hijo
    }
    
    return 0;
}
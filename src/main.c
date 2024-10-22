#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include "backup.h"

int main(int argc, char *argv[]) {
    int parentToChild[2];
    int childToParent[2];
    
    if (pipe(parentToChild) == -1) {
        perror("Error al crear el pipe de padre a hijo");
        exit(EXIT_FAILURE);
    }
    
    if (pipe(childToParent) == -1) {
        perror("Error al crear el pipe de hijo a padre");
        exit(EXIT_FAILURE);
    }
    
    pid_t pid = fork();
    
    if (pid == -1) {
        perror("Error al hacer fork");
        exit(EXIT_FAILURE);
    }
    
    if (pid == 0) {
        // Proceso hijo
        close(parentToChild[1]); // Cierra escritura
        close(childToParent[0]); // Cierra lectura
        proceso_hijo(parentToChild, childToParent, argv[1], argv[2]);
        close(parentToChild[0]); // Cierra lectura
        close(childToParent[1]); // Cierra escritura
    } else {
        // Proceso padre
        close(parentToChild[0]); // Cierra lectura
        close(childToParent[1]); // Cierra escritura
        proceso_padre(argv[1], argv[2], parentToChild, childToParent);
        close(parentToChild[1]); // Cierra escritura
        close(childToParent[0]); // Cierra lectura
        
        wait(NULL); // Espera al hijo
    }
    
    return 0;
}
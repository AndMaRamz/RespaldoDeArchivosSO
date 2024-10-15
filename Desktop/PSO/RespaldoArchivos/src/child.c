#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "backup.h"

void respaldar_archivo(const char *archivo_origen, const char *archivo_destino) {
    char comando[512];
    snprintf(comando, sizeof(comando), "cp %s %s", archivo_origen, archivo_destino);
    system(comando);
}

void proceso_hijo(int pipefd[2], const char *directorio_origen, const char *directorio_respaldo) {
    char buffer[256];
    int total_archivos;
    
    // Leer el número total de archivos del padre
    read(pipefd[0], buffer, sizeof(buffer));
    total_archivos = atoi(buffer);
    
    printf("HIJO(pid=%d) esperando mensaje de mi padre...\n", getpid());
    printf("HIJO(pid=%d) , instrucción de mi padre: Hola hijo, realiza el respaldo de archivos\n", getpid());
    printf("HIJO(pid=%d) , mensaje de mi padre: ¿Cuántos archivos?\n", getpid());
    
    int archivos_restantes = total_archivos;
    
    while (1) {
        read(pipefd[0], buffer, sizeof(buffer));
        
        if (strcmp(buffer, "FIN") == 0) {
            printf("HIJO (pid=%d): Adiós padre, terminé el respaldo!\n", getpid());
            break;
        }
        
        // Respalda el archivo
        char archivo_destino[256];
        snprintf(archivo_destino, sizeof(archivo_destino), "%s/%s", directorio_respaldo, strrchr(buffer, '/') + 1);
        respaldar_archivo(buffer, archivo_destino);
        
        printf("\tHIJO (pid=%d), respaldándoselos el archivo %s\t| Pendientes: %d/%d\n", getpid(), strrchr(buffer, '/') + 1, --archivos_restantes, total_archivos);
    }
    
    // Enviar el número de archivos respaldados al padre
    snprintf(buffer, sizeof(buffer), "%d", total_archivos);
    write(pipefd[1], buffer, sizeof(buffer));
}
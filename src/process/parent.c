#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/stat.h>
#include <time.h>
#include "backup.h"

void crear_directorio_respaldo(const char *directorio_respaldo) {
    struct stat st = {0};
    
    // Verifica si directorio existe
    if (stat(directorio_respaldo, &st) == 0) {
        printf("PADRE: Borrando respaldo viejo...\n");
        // Elimina el directorio de respaldo viejo
        char comando[256];
        snprintf(comando, sizeof(comando), "rm -rf %s", directorio_respaldo);
        system(comando);
    }
    
    // Crear el nuevo directorio de respaldo
    printf("PADRE: Creando nuevo directorio de respaldo '%s'\n", directorio_respaldo);
    mkdir(directorio_respaldo, 0700);
}

void proceso_padre(const char *directorio_origen, const char *directorio_respaldo, int pipefd[2]) {
    crear_directorio_respaldo(directorio_respaldo);
    
    DIR *dir;
    struct dirent *ent;
    int total_archivos = 0;
    
    // Lista archivos del directorio de origen
    dir = opendir(directorio_origen);
    if (dir == NULL) {
        perror("No se puede abrir el directorio");
        exit(EXIT_FAILURE);
    }
    
    // Contar archivos
    while ((ent = readdir(dir)) != NULL) {
        if (ent->d_type == DT_REG) {
            total_archivos++;
        }
    }
    rewinddir(dir); // Reinicia el puntero del directorio
    
    printf("PADRE(pid=%d): generándotela LISTA DE ARCHIVOS A RESPALDAR\n", getpid());
    
    // Enviar el número total de archivos al hijo
    char buffer[256];
    snprintf(buffer, sizeof(buffer), "%d", total_archivos);
    write(pipefd[1], buffer, sizeof(buffer));
    
    printf("—————— > RESPALDANDO %d ARCHIVOS <——————\n", total_archivos);
    
    // Enviar nombres de los archivos uno por uno al hijo
    int archivos_restantes = total_archivos;
    while ((ent = readdir(dir)) != NULL) {
        if (ent->d_type == DT_REG) {
            snprintf(buffer, sizeof(buffer), "%s/%s", directorio_origen, ent->d_name);
            printf("(PADRE —> %s)\n", ent->d_name);
            write(pipefd[1], buffer, sizeof(buffer));
            archivos_restantes--;
        }
    }
    
    // Enviar mensaje de finalización
    snprintf(buffer, sizeof(buffer), "FIN");
    write(pipefd[1], buffer, sizeof(buffer));
    
    // Esperar la respuesta del hijo
    read(pipefd[0], buffer, sizeof(buffer));
    printf("PADRE (pid=%d) recibió un total de %s archivos respaldados exitosamente.\n", getpid(), buffer);
    
    closedir(dir);
    printf("Terminó el proceso padre.\n");
}
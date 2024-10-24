#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "backup.h"

extern const char   *CHILD_WAITING_PARENT_MESSAGE,
                    *CHILD_PARENT_INSTRUCTIONS_MESSAGE,
                    *CHILD_PARENT_FILES_COUNT_MESSAGE,
                    *CHILD_PARENT_END_NOTIFY_MESSAGE,
                    *CHILD_PENDING_FILES_MESSAGE,
                    *END_PROCESS_FLAG,
                    *FORMAT_BUILD_PATH,
                    *FORMAT_COMMAND_COPY,
                    *FORMAT_INT;

void respaldar_archivo(const char *archivo_origen, const char *archivo_destino) {
    char comando[COMMAND_SIZE];
    snprintf(comando, COMMAND_SIZE, FORMAT_COMMAND_COPY, archivo_origen, archivo_destino);
    system(comando);
}

void proceso_hijo(
    int parentToChild[PIPE_FILE_DESCRIPTOR], 
    int childToParent[PIPE_FILE_DESCRIPTOR], 
    const char *directorio_origen, 
    const char *directorio_respaldo
) {
    char buffer[BUFFER_SIZE];
    int total_archivos;
    
    read(parentToChild[PIPE_READ_SIDE], buffer, BUFFER_SIZE);
    total_archivos = atoi(buffer);
    
    printf(CHILD_WAITING_PARENT_MESSAGE, getpid());
    printf(CHILD_PARENT_INSTRUCTIONS_MESSAGE, getpid());
    
    int archivos_restantes = total_archivos;
    printf(CHILD_PARENT_FILES_COUNT_MESSAGE, getpid(), total_archivos);
    
    while (1) {
        read(parentToChild[PIPE_READ_SIDE], buffer, BUFFER_SIZE);
        
        if (strcmp(buffer, END_PROCESS_FLAG) == 0) {
            printf(CHILD_PARENT_END_NOTIFY_MESSAGE, getpid());
            break;
        }
        
        char archivo_destino[FILE_PATH_SIZE];
        snprintf(
            archivo_destino, 
            FILE_PATH_SIZE, 
            FORMAT_BUILD_PATH, directorio_respaldo, 
            strrchr(buffer, SLASH_CHAR) + 1
        );
        respaldar_archivo(buffer, archivo_destino);
        
        printf(
            CHILD_PENDING_FILES_MESSAGE, 
            getpid(), 
            strrchr(buffer, SLASH_CHAR) + 1, 
            --archivos_restantes, 
            total_archivos
        );
    }
    
    snprintf(buffer, BUFFER_SIZE, FORMAT_INT, total_archivos);
    write(childToParent[PIPE_WRITE_SIDE], buffer, BUFFER_SIZE);
}
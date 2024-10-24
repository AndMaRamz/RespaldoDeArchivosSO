#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/stat.h>
#include <time.h>
#include "backup.h"

extern const char   *OPEN_FOLDER_ERROR_MESSAGE,
                    *PARENT_LIST_FILES_MESSAGE,
                    *PARENT_DELETE_FOLDER_MESSAGE,
                    *PARENT_CREATE_FOLDER_MESSAGE,
                    *PARENT_PROCESS_START_MESSAGE,
                    *PARENT_FILES_COUNT_MESSAGE,
                    *PARENT_SEND_COPY_FILE,
                    *PARENT_PROCESS_END_MESSAGE,
                    *END_PROCESS_FLAG,
                    *FORMAT_BUILD_PATH,
                    *FORMAT_COMMAND_REMOVE_FOLDER,
                    *FORMAT_COMMAND_RECUSRIVE_PROGRAM_CALL,
                    *FORMAT_INT,
                    *SAME_FOLDER_LINK,
                    *BACK_FOLDER_LINK;

void crear_directorio_respaldo(const char *directorio_respaldo) {
    struct stat st = {0};
    
    if (stat(directorio_respaldo, &st) == 0) {
        printf(PARENT_DELETE_FOLDER_MESSAGE, getpid());
        // Elimina el directorio de respaldo viejo
        char comando[COMMAND_SIZE];
        snprintf(comando, COMMAND_SIZE, FORMAT_COMMAND_REMOVE_FOLDER, directorio_respaldo);
        system(comando);
    }
    
    printf(PARENT_CREATE_FOLDER_MESSAGE, getpid(), directorio_respaldo);
    mkdir(directorio_respaldo, 0700);
}

void proceso_padre(
    const char *directorio_origen, 
    const char *directorio_respaldo, 
    int parentToChild[PIPE_FILE_DESCRIPTOR], 
    int childToParent[PIPE_FILE_DESCRIPTOR]
) {
    crear_directorio_respaldo(directorio_respaldo);
    
    DIR *dir;
    struct dirent *ent;
    int total_archivos = 0;
    
    dir = opendir(directorio_origen);
    if (dir == NULL) {
        perror(OPEN_FOLDER_ERROR_MESSAGE);
        exit(EXIT_FAILURE);
    }
    
    while ((ent = readdir(dir)) != NULL) {
        if (ent->d_type == DT_REG) {
            total_archivos++;
        }
    }
    rewinddir(dir);
    
    printf(PARENT_LIST_FILES_MESSAGE, getpid());
    
    char buffer[BUFFER_SIZE];
    snprintf(buffer, BUFFER_SIZE, FORMAT_INT, total_archivos);
    write(parentToChild[PIPE_WRITE_SIDE], buffer, BUFFER_SIZE);
    
    printf(PARENT_PROCESS_START_MESSAGE, getpid(), total_archivos);
    
    int archivos_restantes = total_archivos;
    while ((ent = readdir(dir)) != NULL) {
        if (ent->d_type == DT_REG) {
            snprintf(buffer, BUFFER_SIZE, FORMAT_BUILD_PATH, directorio_origen, ent->d_name);
            printf(PARENT_SEND_COPY_FILE, getpid(), ent->d_name);
            write(parentToChild[PIPE_WRITE_SIDE], buffer, BUFFER_SIZE);
            archivos_restantes--;
        } else if(ent->d_type == DT_DIR) {
            if(!strcmp(ent->d_name, SAME_FOLDER_LINK) || !strcmp(ent->d_name, BACK_FOLDER_LINK))
                continue;

            char origen[FILE_PATH_SIZE], destino[FILE_PATH_SIZE], comando[COMMAND_SIZE];
            snprintf(origen, FILE_PATH_SIZE, FORMAT_BUILD_PATH, directorio_origen, ent->d_name);
            snprintf(destino, FILE_PATH_SIZE, FORMAT_BUILD_PATH, directorio_respaldo, ent->d_name);
            snprintf(comando, COMMAND_SIZE, FORMAT_COMMAND_RECUSRIVE_PROGRAM_CALL, origen, destino);
            system(comando);
        }
    }

    snprintf(buffer, BUFFER_SIZE, END_PROCESS_FLAG, getpid());
    write(parentToChild[PIPE_WRITE_SIDE], buffer, BUFFER_SIZE);
        
    read(childToParent[PIPE_READ_SIDE], buffer, BUFFER_SIZE);
    printf(PARENT_FILES_COUNT_MESSAGE, getpid(), buffer);

    closedir(dir);
    printf(PARENT_PROCESS_END_MESSAGE, getpid());
}
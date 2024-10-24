#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include "backup.h"

extern const char *PIPE_CREATION_ERROR_MESSAGE, *PROCESS_CLONE_ERROR_MESSAGE;

int main(int argc, char *argv[]) {
    int parentToChild[PIPE_FILE_DESCRIPTOR];
    int childToParent[PIPE_FILE_DESCRIPTOR];
    
    if (pipe(parentToChild) == PIPE_CREATION_ERROR) {
        perror(PIPE_CREATION_ERROR_MESSAGE);
        exit(EXIT_FAILURE);
    }
    
    if (pipe(childToParent) == PIPE_CREATION_ERROR) {
        perror(PIPE_CREATION_ERROR_MESSAGE);
        exit(EXIT_FAILURE);
    }
    
    pid_t pid = fork();
    
    if (pid == PROCESS_ID_ERROR) {
        perror(PROCESS_CLONE_ERROR_MESSAGE);
        exit(EXIT_FAILURE);
    }
    
    if (pid == PROCESS_ID_CHILD) {
        close(parentToChild[PIPE_WRITE_SIDE]);
        close(childToParent[PIPE_READ_SIDE]);
        proceso_hijo(parentToChild, childToParent, argv[PROGRAM_SOURCE_ARG], argv[PROGRAM_DESTINY_ARG]);
        close(parentToChild[PIPE_READ_SIDE]);
        close(childToParent[PIPE_WRITE_SIDE]);
    } else {
        close(parentToChild[PIPE_READ_SIDE]);
        close(childToParent[PIPE_WRITE_SIDE]);
        proceso_padre(argv[PROGRAM_SOURCE_ARG], argv[PROGRAM_DESTINY_ARG], parentToChild, childToParent);
        close(parentToChild[PIPE_WRITE_SIDE]);
        close(childToParent[PIPE_READ_SIDE]);
        
        waitpid(pid, NULL, 0);
    }
    
    return EXIT_SUCCESS;
}
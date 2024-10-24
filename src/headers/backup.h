#ifndef BACKUP_H
#define BACKUP_H

#define BUFFER_SIZE             256
#define FILE_PATH_SIZE          512
#define COMMAND_SIZE            1024

#define PIPE_FILE_DESCRIPTOR    2
#define PIPE_READ_SIDE          0
#define PIPE_WRITE_SIDE         1

#define PIPE_CREATION_ERROR     -1

#define PROCESS_ID_ERROR        -1
#define PROCESS_ID_CHILD        0

#define PROGRAM_SOURCE_ARG      1
#define PROGRAM_DESTINY_ARG     2

#define SLASH_CHAR              '/'

void crear_directorio_respaldo(const char *);
void respaldar_archivo(const char *, const char *);
void proceso_padre(const char *, const char *, int [PIPE_FILE_DESCRIPTOR], int [PIPE_FILE_DESCRIPTOR]);
void proceso_hijo(int[PIPE_FILE_DESCRIPTOR], int[PIPE_FILE_DESCRIPTOR], const char *, const char *);

#endif // BACKUP_H

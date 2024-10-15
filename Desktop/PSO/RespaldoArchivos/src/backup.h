#ifndef BACKUP_H
#define BACKUP_H

void crear_directorio_respaldo(const char *directorio_respaldo);
void respaldar_archivo(const char *archivo_origen, const char *archivo_destino);
void proceso_padre(const char *directorio_origen, const char *directorio_respaldo, int pipefd[2]);
void proceso_hijo(int pipefd[2], const char *directorio_origen, const char *directorio_respaldo);

#endif // BACKUP_H

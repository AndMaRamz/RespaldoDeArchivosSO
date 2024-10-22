#ifndef BACKUP_H
#define BACKUP_H

void crear_directorio_respaldo(const char *);
void respaldar_archivo(const char *, const char *);
void proceso_padre(const char *, const char *, int [2], int [2]);
void proceso_hijo(int[2], int[2], const char *, const char *);

#endif // BACKUP_H

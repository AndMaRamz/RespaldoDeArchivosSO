const char *PIPE_CREATION_ERROR_MESSAGE = "Error al crear el pipe.";
const char *PROCESS_CLONE_ERROR_MESSAGE = "Error al realizar el fork.";
const char *OPEN_FOLDER_ERROR_MESSAGE = "No se puede abrir el directorio";

const char *PARENT_LIST_FILES_MESSAGE = "PADRE(pid=%d): Generando lista de archivos a respaldar.\n";
const char *PARENT_DELETE_FOLDER_MESSAGE = "PADRE(pid=%d): Borrando respaldo viejo.\n";
const char *PARENT_CREATE_FOLDER_MESSAGE = "PADRE(pid=%d): Creando nuevo directorio de respaldo '%s'\n";
const char *PARENT_PROCESS_START_MESSAGE = "——————> RESPALDANDO %d ARCHIVOS <——————\n";
const char *PARENT_FILES_COUNT_MESSAGE = "PADRE(pid=%d): Se recibieron un total de %s archivos respaldados exitosamente.\n";
const char *PARENT_SEND_COPY_FILE = "PADRE(pid=%d): Enviando archivo a respaldar '%s'\n";
const char *PARENT_PROCESS_END_MESSAGE = "PADRE(pid=%d): Terminó el proceso padre.\n";

const char *CHILD_WAITING_PARENT_MESSAGE = "\tHIJO(pid=%d): Esperando mensaje de mi padre.\n";
const char *CHILD_PARENT_INSTRUCTIONS_MESSAGE = "\tHIJO(pid=%d): Instrucción de mi padre: Hola hijo, realiza el respaldo de archivos.\n";
const char *CHILD_PARENT_FILES_COUNT_MESSAGE = "\tHIJO(pid=%d): Mensaje de mi padre, clona %d archivos.\n";
const char *CHILD_PARENT_END_NOTIFY_MESSAGE = "\tHIJO(pid=%d): Adiós padre, terminé el respaldo!\n";
const char *CHILD_PENDING_FILES_MESSAGE = "\tHIJO(pid=%d): Respaldándoselos el archivo '%s'\t| Pendientes: %d/%d\n";

const char *END_PROCESS_FLAG = "-FIN-";

const char *FORMAT_BUILD_PATH = "%s/%s";
const char *FORMAT_INT = "%d";
const char *FORMAT_COMMAND_REMOVE_FOLDER = "rm -rf %s";
const char *FORMAT_COMMAND_RECUSRIVE_PROGRAM_CALL = "./programa %s %s";
const char *FORMAT_COMMAND_COPY = "cp %s %s";

const char *SAME_FOLDER_LINK = ".";
const char *BACK_FOLDER_LINK = "..";
#ifndef SERVER_CPU_H_
#define SERVER_CPU_H_

#include <stdint.h>
#include <string.h>
#include <pthread.h>
#include <inttypes.h>
#include <commons/log.h>
#include <stdint.h> //Distintos tipos de INT
#include "../../shared/include/sockets.h"
#include "../../shared/include/protocolo.h"

int server_escuchar(t_log *logger, char *server_name, int server_socket);

typedef struct
{
    t_log *log;
    int fd;
    char *server_name;
} t_procesar_conexion_args;

static void procesar_conexion(void *void_args);

#endif

#ifndef MEMORY_COMUNICACION_H
#define MEMORY_COMUNICACION_H
#include "../../shared/include/utils.h"
#include "../../shared/include/sockets.h"
#include "../../shared/include/protocolo.h"
#include <commons/config.h>
#include <commons/log.h>
#include "../include/init_memory.h" //Para tener logger y config
#include <stdint.h>                 //Distintos tipos de INT
#include <stdio.h>                  //Para incluir NULL
#include <pthread.h>                //Para hilos
typedef struct
{
    int fd;
    char *server_name;
} t_procesar_conexion;

// Recibe algún send o recv y lo procesa
static void procesar_conexion(void *void_args);
// Escucha activamente por clientes
int server_escuchar(char *server_name, int server_socket);

#endif
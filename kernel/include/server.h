#ifndef SERVER_KERNEL_H_
#define SERVER_KERNEL_H_

#include <stdint.h>
#include <string.h>
#include <pthread.h>
#include <inttypes.h>
#include <commons/log.h>
#include <stdint.h> //Distintos tipos de INT

#include "../../shared/include/sockets.h"
#include "../../shared/include/protocolo.h"

int server_escuchar(t_log *logger, char *server_name, int server_socket);
void kernel_escuchando(void *arguments);
void server_escuchar_v2(t_log *logger, char *server_name, int server_socket);
#endif

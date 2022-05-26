#ifndef PROTOCOLO_H_
#define PROTOCOLO_H_

#include <inttypes.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>

// typedef enum
// {
//     APROBAR_OPERATIVOS,
//     MIRAR_NETFLIX,
//     DEBUG = 69,
// } op_code;

///

typedef enum
{
        NO_OP = 1,
        IO,
        READ,
        COPY,
        WRITE,
        EXIT = 6,
        // Memoria espera mensajes de CPU Y KERNEL:
        START_PROCESS = 7,
        SUSPEND_PROCESS,
        END_PROCESS,
        ACCESS_TO_TABLE_PAGES,
        ACCESS_TO_USER_SPACE_READ,
        ACCESS_TO_USER_SPACE_WRITE = 12
} op_code;

// bool send_aprobar_operativos(int fd, uint8_t nota1, uint8_t nota2);
// bool recv_aprobar_operativos(int fd, uint8_t *nota1, uint8_t *nota2);

// bool send_mirar_netflix(int fd, char *peli, uint8_t cant_pochoclos);
// bool recv_mirar_netflix(int fd, char **peli, uint8_t *cant_pochoclos);

// bool send_debug(int fd);

bool send_unit32_t(int fd, uint32_t cantidad, op_code codigo_operacion);
bool recv_uint32_t(int fd, uint32_t *cantidad);

bool send_dos_uint32_t(int fd, uint32_t nota1, uint32_t nota2, op_code codigo_operacion);
bool recv_dos_uint32_t(int fd, uint32_t *nota1, uint32_t *nota2);

bool send_exit(int fd);

#endif
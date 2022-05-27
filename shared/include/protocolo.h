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

static void *serializar_uint32_t(uint32_t cantidad, op_code codigoOperacion);
/*  @NAME: serializar_uint32_t
    @DESC: Me va a servir para serializar NO_OP, I/O , READ. Es una funcion aux para el send
    @PARAMETROS:
                 - cantidad: es ul uint8_t que queremos serializar
                 - codigoOperacion: es el codigo de operacion que corresponde. Se lo agregamos ya que con una funcion
                   serializamos 3 codigos(serian NO_OP, IO , READ)

    @RETORNO: un stream

    @EJEMPLOS: serializar_uint32_t(5,NO_OP);
    */

bool send_unit32_t(int fd, uint32_t cantidad, op_code codigo_operacion);
bool recv_uint32_t(int fd, uint32_t *cantidad);

bool send_dos_uint32_t(int fd, uint32_t param1, uint32_t param2, op_code codigo_operacion);
bool recv_dos_uint32_t(int fd, uint32_t *param1, uint32_t *param2);

/* serializar_dos_uint8_t: nos va a servir para serializar NO_OP , I/O , READ
    Debido a que los 3 reciben los mismos parametros se serializan igual
    le pongo el codigo de operacion como parametro de la funcion para cuando lo enviemos
*/
static void *serializar_dos_uint32_t(uint32_t param1, uint32_t param2, op_code codigo_operacion);

static void deserializar_dos_uint32_t(void *stream, uint32_t *param1, uint32_t *param2);

bool send_exit(int fd);
// NO es necesario hacer un recv_exit pq no recibe nada, el op_code ya lo tengo

#endif
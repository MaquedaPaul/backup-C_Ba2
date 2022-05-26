#include "../include/protocolo.h"

/*  @NAME: serializar_uint8_t
    @DESC: Me va a servir para serializar NO_OP, I/O , READ. Es una funcion aux para el send
    @PARAMETROS:
                 - cantidad: es ul uint8_t que queremos serializar
                 - codigoOperacion: es el codigo de operacion que corresponde. Se lo agregamos ya que con una funcion
                   serializamos 3 codigos(serian NO_OP, IO , READ)

    @RETORNO: un stream

    @EJEMPLOS: serializar_uint8_t(5,NO_OP);
 */

static void *serializar_uint32_t(uint32_t cantidad, op_code codigoOperacion)
{

    void *stream = malloc(sizeof(op_code) + sizeof(uint32_t));

    // memcpy(donde lo guarda,lo que va a ser copiado,tamaño de lo que va a guardar)
    memcpy(stream, &codigoOperacion, sizeof(op_code));
    memcpy(stream + sizeof(op_code), &cantidad, sizeof(uint32_t));
    return stream;
}

static void deserializar_uint32_t(void *stream, uint32_t *cantidad)
{
    memcpy(cantidad, stream, sizeof(uint32_t));
}

// send(int socket, stream , tamaño Total del stream , 0)

bool send_uint32_t(int fd, uint32_t cantidad, op_code codigo_operacion)
{
    size_t size = sizeof(op_code) + sizeof(uint32_t);
    void *stream = serializar_uint32_t(cantidad, codigo_operacion);
    if (send(fd, stream, size, 0) != size)
    {
        free(stream);
        return false;
    }
    free(stream);
    return true;
}

bool recv_uint32_t(int fd, uint32_t *cantidad)
{
    size_t size = sizeof(uint32_t);
    void *stream = malloc(size);

    if (recv(fd, stream, size, 0) != size)
    {
        free(stream);
        return false;
    }

    deserializar_uint32_t(stream, cantidad);

    free(stream);
    return true;
}

/* serializar_dos_uint8_t: nos va a servir para serializar NO_OP , I/O , READ
    Debido a que los 3 reciben los mismos parametros se serializan igual
    le pongo el codigo de operacion como parametro de la funcion para cuando lo enviemos
*/

static void *serializar_dos_uint32_t(uint32_t nota1, uint32_t nota2, op_code codigo_operacion)
{
    void *stream = malloc(sizeof(op_code) + sizeof(uint32_t) * 2);

    memcpy(stream, &codigo_operacion, sizeof(op_code));
    memcpy(stream + sizeof(op_code), &nota1, sizeof(uint32_t));
    memcpy(stream + sizeof(op_code) + sizeof(uint32_t), &nota2, sizeof(uint32_t));
    return stream;
}

static void deserializar_dos_uint32_t(void *stream, uint32_t *nota1, uint32_t *nota2)
{
    memcpy(nota1, stream, sizeof(uint32_t));
    memcpy(nota2, stream + sizeof(uint32_t), sizeof(uint32_t));
}

bool send_dos_uint32_t(int fd, uint32_t nota1, uint32_t nota2, op_code codigo_operacion)
{
    size_t size = sizeof(op_code) + sizeof(uint32_t) * 2;
    void *stream = serializar_dos_uint32_t(nota1, nota2, codigo_operacion);
    if (send(fd, stream, size, 0) != size)
    {
        free(stream);
        return false;
    }
    free(stream);
    return true;
}

bool recv_dos_uint32_t(int fd, uint32_t *nota1, uint32_t *nota2)
{
    size_t size = sizeof(uint32_t) * 2;
    void *stream = malloc(size);

    if (recv(fd, stream, size, 0) != size)
    {
        free(stream);
        return false;
    }

    deserializar_dos_uint32_t(stream, nota1, nota2);

    free(stream);
    return true;
}

bool send_exit(int fd)
{
    op_code cop = EXIT;
    if (send(fd, &cop, sizeof(op_code), 0) != sizeof(op_code))
        return false;
    return true;
}

// NO es necesario hacer un recv_exit pq no recibe nada, el op_code ya lo tengo
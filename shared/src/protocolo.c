#include "../include/protocolo.h"

static void *serializar_handshake(uint32_t handshake)
{

    void *stream = malloc(sizeof(op_code) + sizeof(uint32_t));
    op_code codigoOperacion = HANDSHAKE;
    // memcpy(donde lo guarda,lo que va a ser copiado,tamaño de lo que va a guardar)
    memcpy(stream, &codigoOperacion, sizeof(op_code));
    memcpy(stream + sizeof(op_code), &handshake, sizeof(uint32_t));
    return stream;
}

static void deserializar_handshake(void *stream, uint32_t *handshake)
{
    memcpy(handshake, stream, sizeof(uint32_t));
}

// send(int socket, stream , tamaño Total del stream , 0)

bool sendHandShake(int fd, uint32_t cantidad)
{
    op_code codigo_operacion = HANDSHAKE;
    size_t size = sizeof(op_code) + sizeof(uint32_t);
    void *stream = serializar_handshake(cantidad);
    if (send(fd, stream, size, 0) != size)
    {
        free(stream);
        return false;
    }
    free(stream);
    return true;
}

bool recvHandShake(int fd, uint32_t *cantidad)
{
    size_t size = sizeof(uint32_t);
    void *stream = malloc(size);

    if (recv(fd, stream, size, 0) != size)
    {
        free(stream);
        return false;
    }

    deserializar_handshake(stream, cantidad);

    free(stream);
    return true;
}

static void *serializar_uint32_t(uint32_t unEntero, op_code codigoOperacion)
{

    void *stream = malloc(sizeof(op_code) + sizeof(uint32_t));

    // memcpy(donde lo guarda,lo que va a ser copiado,tamaño de lo que va a guardar)
    memcpy(stream, &codigoOperacion, sizeof(op_code));
    memcpy(stream + sizeof(op_code), &unEntero, sizeof(uint32_t));
    return stream;
}

static void deserializar_uint32_t(void *stream, uint32_t *unEntero)
{
    memcpy(unEntero, stream, sizeof(uint32_t));
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

static void *serializar_dos_uint32_t(uint32_t param1, uint32_t param2, op_code codigo_operacion)
{
    void *stream = malloc(sizeof(op_code) + sizeof(uint32_t) * 2);

    memcpy(stream, &codigo_operacion, sizeof(op_code));
    memcpy(stream + sizeof(op_code), &param1, sizeof(uint32_t));
    memcpy(stream + sizeof(op_code) + sizeof(uint32_t), &param2, sizeof(uint32_t));
    return stream;
}

static void deserializar_dos_uint32_t(void *stream, uint32_t *param1, uint32_t *param2)
{
    memcpy(param1, stream, sizeof(uint32_t));
    memcpy(param2, stream + sizeof(uint32_t), sizeof(uint32_t));
}

bool send_dos_uint32_t(int fd, uint32_t param1, uint32_t param2, op_code codigo_operacion)
{
    size_t size = sizeof(op_code) + sizeof(uint32_t) * 2;
    void *stream = serializar_dos_uint32_t(param1, param2, codigo_operacion);
    if (send(fd, stream, size, 0) != size)
    {
        free(stream);
        return false;
    }
    free(stream);
    return true;
}

bool recv_dos_uint32_t(int fd, uint32_t *param1, uint32_t *param2)
{
    size_t size = sizeof(uint32_t) * 2;
    void *stream = malloc(size);

    if (recv(fd, stream, size, 0) != size)
    {
        free(stream);
        return false;
    }

    deserializar_dos_uint32_t(stream, param1, param2);

    free(stream);
    return true;
}
/////////////////////////////
/*
bool send_exit(int fd)
{
    op_code cop = EXIT;
    if (send(fd, &cop, sizeof(op_code), 0) != sizeof(op_code))
        return false;
    return true;
}
*/
/////////////////////////////////

// NO es necesario hacer un recv_exit pq no recibe nada, el op_code ya lo tengo

static op_code recibir_cop(int fd)
{
    op_code cop;
    if (recv(fd, &cop, sizeof(op_code), 0) != 0)
        return cop;
    else
    {
        close(fd);
        return -1;
    }
}

bool send_op_code(int fd, int unOp_code)
{
    op_code cop = unOp_code;
    if (send(fd, &cop, sizeof(op_code), 0) != sizeof(op_code))
    {
        return false;
    }
    return true;
}
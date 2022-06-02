#include "../include/server.h"

typedef struct
{
    t_log *log;
    int fd;
    char *server_name;
} t_procesar_conexion_args;

static void procesar_conexion(void *void_args)
{
    t_procesar_conexion_args *args = (t_procesar_conexion_args *)void_args;
    t_log *logger = args->log;
    int cliente_socket = args->fd;
    char *server_name = args->server_name;
    free(args);

    op_code cop;
    while (cliente_socket != -1)
    {

        if (recv(cliente_socket, &cop, sizeof(op_code), 0) != sizeof(op_code))
        {
            log_info(logger, "DISCONNECT!");
            return;
        }

        switch (cop)
        {

        case HANDSHAKE:
        {
            uint32_t apreton;

            if (!recvHandShake(cliente_socket, &apreton))
            {
                log_error(logger, "Fallo recibiendo HANDSHAKE");
                break;
            }
            printf("Handshake recibido, %i", apreton);
        }

            /*
                    case NO_OP:
                    {
                        uint32_t cantidad;

                        if (!recv_uint32_t(cliente_socket, &cantidad))
                        {
                            log_error(logger, "Fallo recibiendo NO_OP");
                            break;
                        }

                        log_info(logger, "Tengo que hacer %u operaciones de NO_OP ", cantidad);
                        break;
                    }

                    case IO:
                    {
                        uint32_t tiempo;
                        if (!recv_uint32_t(cliente_socket, &tiempo))
                        {
                            log_error(logger, "Fallo recibiendo IO");
                            break;
                        }

                        log_info(logger, "Me debo bloquear por %u  milisegundos", tiempo);
                        break;
                    }

                    case READ:
                    {

                        uint32_t direccion_logica;
                        if (!recv_uint32_t(cliente_socket, &direccion_logica))
                        {
                            log_error(logger, "Fallo recibiendo READ");
                            break;
                        }
                        log_info(logger, "Debo leer el valor de memoria correspondiente a la dir %u y luego imprimirlo por pantalla", direccion_logica);
                        break;
                    }

                    case WRITE:
                    {
                        uint32_t direccion_logica;
                        uint32_t valor;
                        if (!recv_dos_uint32_t(cliente_socket, &direccion_logica, &valor))
                        {
                            log_error(logger, "Fallo recibiendo WRITE");
                            break;
                        }
                        log_info(logger, "Debo escribir en memoria el valor %u en el espacio %u", valor, direccion_logica);
                        break;
                    }

                    case COPY:
                    {
                        uint32_t direccion_logica_destino;
                        uint32_t direccion_logica_origen;
                        if (!recv_dos_uint32_t(cliente_socket, &direccion_logica_destino, &direccion_logica_origen))
                        {
                            log_error(logger, "Fallo recibiendo COPY");
                            break;
                        }
                        log_info(logger, "Debo escribir en %u el valor contenido dentro de %u", direccion_logica_destino, direccion_logica_origen);
                        break;
                    }

                    case EXIT:
                        log_info(logger, "EXIT");
                        break;
            */
        // Errores
        case -1:
            log_error(logger, "Cliente desconectado de %s...", server_name);
            return;
        default:
            log_error(logger, "Algo anduvo mal en el server de %s", server_name);
            log_info(logger, "Cop: %d", cop);
            return;
        }
    }

    log_warning(logger, "El cliente se desconecto de %s server", server_name);
    return;
}

int server_escuchar(t_log *logger, char *server_name, int server_socket)
{
    int cliente_socket = esperar_cliente(logger, server_name, server_socket);

    if (cliente_socket != -1)
    {
        pthread_t hilo;
        t_procesar_conexion_args *args = malloc(sizeof(t_procesar_conexion_args));
        args->log = logger;
        args->fd = cliente_socket;
        args->server_name = server_name;
        pthread_create(&hilo, NULL, (void *)procesar_conexion, (void *)args);
        pthread_detach(hilo);
        return 1;
    }
    return 0;
}
/*
int generar_conexiones(t_log *logger, char *server_name, int server_socket){


}
*/
/*
bool generar_conexiones(t_log *logger, int *fd_kernel)
{
    // No hardcodear, levantar de config
    char *ip_kernel;
    char *puerto_kernel;

    t_config *configKernelConnection = iniciar_config("./kernel.config");
    ip_kernel = config_get_string_value(configKernelConnection, "IP_KERNEL");
    log_info(logger, "IP Cargada %s", ip_kernel);
    puerto_kernel = config_get_string_value(configKernelConnection, "PUERTO_KERNEL");
    log_info(logger, "Puerto Cargado %s", puerto_kernel);

    // char *port_kernel = "6969";
    //  char *port_mod3 = "4200";
    // char *ip_kernel = "0.0.0.0";
    //  char *ip_mod3 = "0.0.0.0";

    *fd_kernel = crear_conexion(logger, "KERNEL", ip_kernel, puerto_kernel); // es el que acopla, pero antes te tienen que estar esperando

    return *fd_kernel != 0; //&& *fd_cpu != 0;
}
*/
#include "include/main.h"

void sighandler(int s)
{
    cerrar_programa(logger);
    exit(0);
}

int main()
{
    /*
        t_log *logger2;
        logger2 = log_create("memory.log", MODULENAME, false, LOG_LEVEL_INFO);
        log_info(logger2, "PRUEBA");

    */

    if (!init() || !cargar_configuracion("kernel.config"))
    // cada función va a hacer su operación, si las tres fallan, se cierra la app
    {
        // cerrar_programa(logger2); --> implementar
        return EXIT_FAILURE;
    }

    // signal(SIGINT, sighandler); // Para poder cerrar correctamente el programa apretando CTRL + C
    logger = log_create("kernel.log", "KERNEL", true, LOG_LEVEL_INFO);

    // ****** CREACION DEL SERVIDOR ******

    char *puerto = string_itoa(cfg->PUERTO_ESCUCHA);
    log_info(logger, "Cargado puerto %s", puerto);
    kernel_server = iniciar_servidor(logger, SERVERNAME, "127.0.0.1", puerto);
    log_info(logger, "Iniciando servidor con la IP:PORT 127.0.0.1:%s", puerto);

    while (server_escuchar(logger, SERVERNAME, kernel_server))
    {
    };
    liberar_conexion(kernel_server);

    /////////////////////////////////////////////////////////
    // fd significa file descriptor. Es el socket
    /*
    if (!generar_conexion_cpu_dispatch(logger, &fd_cpu_dispatch))
    {
        cerrar_programa(logger);
        return EXIT_FAILURE;
    }

    uint32_t handshake = 5;
    sendHandShake(fd_cpu_dispatch, handshake);
    op_code cop;
    if (recv(fd_cpu_dispatch, &cop, sizeof(op_code), 0) != sizeof(op_code))
    {
        log_info(logger, "DISCONNECT!");
        return EXIT_FAILURE;
    }
    if (cop == HANDSHAKE)
    {
        uint32_t apreton;
        if (!recvHandShake(fd_cpu_dispatch, &apreton))
        {
            log_error(logger, "Fallo recibiendo HANDSHAKE");
        }
        printf("Handshake recibido, %i \n", apreton);
    }
    else
    {
        printf("codigo de op no reconocido");
    }
*/
    // Prueba como cliente de CPU

    cerrar_programa(logger);

    return EXIT_SUCCESS;
}

//

//
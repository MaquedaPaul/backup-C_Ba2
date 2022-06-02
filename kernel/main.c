#include "include/main.h"

void sighandler(int s)
{
    cerrar_programa(logger);
    exit(0);
}

int main()
{
    t_log *logger2;
    printf("prueba\n");
    logger2 = log_create("memory.log", MODULENAME, false, LOG_LEVEL_INFO);
    log_info(logger2, "PRUEBA");
    printf("hola\n");

    if (!init() || !cargar_configuracion("kernel.config"))
    // cada función va a hacer su operación, si las tres fallan, se cierra la app
    {
        cerrar_programa(logger2);
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
        ;
    liberar_conexion(kernel_server);
    cerrar_programa(logger);

    return 0;
}

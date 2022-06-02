#include "include/main.h"

t_log *logger;
int fd_kernel;
int pid_actual = 0;

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
        cerrar_programa();
        return EXIT_FAILURE;
    }

    char *ip;
    char *puerto;

    signal(SIGINT, sighandler); // Para poder cerrar correctamente el programa apretando CTRL + C
    logger = log_create("kernel.log", "KERNEL", true, LOG_LEVEL_INFO);

    t_config *configKernelAsServer = iniciar_config("./server.config");
    ip = config_get_string_value(configKernelAsServer, "IP_KERNEL");
    log_info(logger, "IP Cargada %s", ip);
    puerto = config_get_string_value(configKernelAsServer, "PUERTO_KERNEL");
    log_info(logger, "Puerto Cargado %s", puerto);

    fd_kernel = iniciar_servidor(logger, "KERNEL", ip, puerto);
    while (server_escuchar(logger, "KERNEL", fd_kernel))
        ;

    cerrar_programa(logger);

    return 0;
}

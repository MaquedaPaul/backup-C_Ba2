#include "include/main.h"

t_log *logger;
int fd_kernel;

void sighandler(int s)
{
    cerrar_programa(logger);
    exit(0);
}

int main()
{
    signal(SIGINT, sighandler);
    logger = iniciar_logger("kernel.log", "KERNEL", true, LOG_LEVEL_INFO);

    t_config *configKernelAsServer = iniciar_config("./server.config");
    ip = config_get_string_value(configKernelAsServer, "IP");
    log_info(logger, "IP Cargada %s", ip);
    puerto = config_get_string_value(configKernelAsServer, "PUERTO");
    log_info(logger, "Puerto Cargado %s", puerto);
    fd_kernel = iniciar_servidor(logger, "KERNEL", ip, puerto);
    while (server_escuchar(logger, "KERNEL", fd_kernel))
        ;

    cerrar_programa(logger);

    return 0;
}

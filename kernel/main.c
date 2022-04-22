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

    logger = log_create("kernel.log", "KERNEL", true, LOG_LEVEL_INFO);

    // No hardcodear IP y puerto, leer de config
    fd_kernel = iniciar_servidor(logger, "KERNEL", "0.0.0.0", "6969");
    while (server_escuchar(logger, "KERNEL", fd_kernel))
        ;

    cerrar_programa(logger);

    return 0;
}

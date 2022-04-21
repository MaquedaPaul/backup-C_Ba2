#include "../include/init.h"

bool generar_conexiones(t_log *logger, int *fd_kernel, int *fd_cpu)
{
    // No hardcodear, levantar de config
    iniciar_config("./kernel.config");
    char *port_kernel = "6969";
    // char *port_mod3 = "4200";
    char *ip_kernel = "0.0.0.0";
    // char *ip_mod3 = "0.0.0.0";

    *fd_kernel = crear_conexion(
        logger,
        "KERNEL",
        ip_kernel,
        port_kernel);
    /*
        *fd_cpu = crear_conexion(
            logger,
            "CPU",
            ip_cpu,
            port_cpu);
    */
    return *fd_kernel != 0 //&& *fd_cpu != 0;
}

void cerrar_programa(t_log *logger)
{
    log_destroy(logger);
}

t_config *iniciar_config(char *path)
{
    t_config *nuevo_config;

    nuevo_config = config_create(path);

    if (nuevo_config == NULL)
    {
        printf("No se pudo leer la config\n");
        exit(2);
    }

    return nuevo_config;
}
#include "../include/conexion.h"

bool generar_conexiones(t_log *logger, int *fd_kernel)
{
    // char *ip = string_itoa(cfg->IP_KERNEL);
    char *puerto = cfg->PUERTO_KERNEL;
    char *ip = cfg->IP_KERNEL;
    *fd_kernel = crear_conexion(logger, "KERNEL", ip, puerto); // es el que acopla, pero antes te tienen que estar esperando

    return *fd_kernel != 0; //&& *fd_cpu != 0;
}

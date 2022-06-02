#include "../include/cliente_cpu.h"

bool generar_conexion_cpu_dispatch(t_log *logger, int *fd_cpu_dispatch)
{

    // PENDIENTE NO HARDCODEAR
    // char *ip_cpu = string_itoa(cfg->IP_CPU);
    // char *puerto_cpu_dispatch = string_itoa(cfg->PUERTO_CPU_DISPATCH);

    *fd_cpu_dispatch = crear_conexion(logger, "CPU", "127.0.0.1", "8001"); // es el que acopla, pero antes te tienen que estar esperando

    return *fd_cpu_dispatch != 0; //&& *fd_cpu != 0;
}

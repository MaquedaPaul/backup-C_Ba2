#ifndef INIT_KERNEL_H_
#define INIT_KERNEL_H_
#define MODULENAME "KERNEL"
#include <commons/log.h>
#include <commons/config.h>
#include "../include/utils.h"

t_log *logger;
t_config_kernel *cfg;

typedef struct
{
    uint32_t IP_MEMORIA;
    uint32_t PUERTO_MEMORIA;
    uint32_t IP_CPU;
    uint32_t PUERTO_CPU_DISPATCH;
    uint32_t PUERTO_CPU_INTERRUPT;
    uint32_t PUERTO_ESCUCHA;
    char *ALGORITMO_PLANIFICACION;
    uint32_t ESTIMACION_INICIAL;
    double ALFA;
    uint8_t GRADO_MULTIPROGRAMACION;
    uint32_t TIEMPO_MAXIMO_BLOQUEADO;
} t_config_kernel;

static t_config_kernel *initialize_cfg()
// Inicializo en NULL para no tener basura
{
    t_config_kernel *cfg = malloc(sizeof(t_config_kernel));
    cfg->ALGORITMO_PLANIFICACION = NULL;
    return cfg;
}

void cerrar_programa(t_log *logger);

#endif

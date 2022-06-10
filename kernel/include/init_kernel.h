#ifndef INIT_KERNEL_H_
#define INIT_KERNEL_H_
#define MODULENAME "KERNEL"
#define SERVERNAME "KERNEL_SERVER"

#include <commons/log.h>
#include <commons/config.h>
#include "../../shared/include/utils.h"
#include "../../shared/include/estructuras.h"
#include <stdlib.h>
#include <string.h>
#include <commons/string.h>
#include "../../shared/include/sockets.h"
#include <stdbool.h>
#include <commons/collections/list.h>

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

t_log *logger;
t_config_kernel *cfg;

static t_config_kernel *initialize_cfg()
// Inicializo en NULL para no tener basura
{
    t_config_kernel *cfg = malloc(sizeof(t_config_kernel));
    cfg->ALGORITMO_PLANIFICACION = NULL;
    return cfg;
}
uint8_t init();
uint8_t cargar_configuracion(char *path);
void inicializar_servidor(int fd);

void cerrar_programa(t_log *logger);

#endif

#ifndef INIT_CPU_H_
#define INIT_CPU_H_
#define MODULENAME "CPU"
#define SERVERNAME "CPU_SERVER"

#include <commons/log.h>
#include <commons/config.h>
#include "../../shared/include/utils.h"
#include <stdlib.h>
#include <string.h>
#include <commons/string.h>
#include "../../shared/include/sockets.h"

typedef struct
{
    uint32_t ENTRADAS_TLB;
    char *REEMPLAZO_TLB;
    uint32_t RETARDO_NOOP;
    uint32_t IP_MEMORIA;
    uint32_t PUERTO_MEMORIA;
    uint32_t PUERTO_ESCUCHA_DISPATCH;
    uint32_t PUERTO_ESCUCHA_INTERRUPT;
} t_config_cpu;

t_log *logger;
t_config_cpu *cfg;

static t_config_cpu *initialize_cfg()
// Inicializo en NULL para no tener basura
{
    t_config_cpu *cfg = malloc(sizeof(t_config_cpu));
    cfg->REEMPLAZO_TLB = NULL;
    return cfg;
}
uint8_t init();
uint8_t cargar_configuracion(char *path);
void inicializar_servidor(int fd);

void cerrar_programa(t_log *logger);

#endif

#ifndef INIT_CONSOLE_H_
#define INIT_CONSOLE_H_
#include <commons/config.h>
#include <commons/log.h>
#include <inttypes.h>
#include "../../shared/include/utils.h"
#include <stdlib.h>
#include <string.h>
#include <commons/string.h>
#define MODULENAME "CONSOLE"
t_log *logger;
t_config *cfg_file;
typedef struct
{
    char *IP_KERNEL;
    char *PUERTO_KERNEL;

} t_config_console;
t_config_console *cfg;

uint8_t cargar_configuracion(char *path);
uint8_t init();

static t_config_console *initialize_cfg()
// Inicializo en NULL para no tener basura
{
    t_config_console *cfg = malloc(sizeof(t_config_console));
    return cfg;
}

#endif // CONEXION_CONSOLE_H

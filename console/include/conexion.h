#ifndef CONEXION_CONSOLE_H
#define CONEXION_CONSOLE_H

#include "../../shared/include/sockets.h"
#include "../../shared/include/protocolo.h"
#include "../../shared/include/manager.h"
#include <commons/config.h>
#include "../include/init_console.h"
extern t_config_console *cfg;
bool generar_conexiones(t_log *logger, int *fd_server);

#endif

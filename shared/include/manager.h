#ifndef MANAGER_H_
#define MANAGER_H_
#include <commons/log.h>
#include <commons/config.h>
#include "../include/sockets.h"
t_config *iniciar_config(char *path);

void terminar_programa(int conexion, t_log *logger, t_config *config);

// t_log *iniciar_logger(char *path, char *name, int debug, int log_level);

#endif
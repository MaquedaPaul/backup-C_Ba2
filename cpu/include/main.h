#ifndef CPU_MAIN_H_
#define CPU_MAIN_H_
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <commons/log.h>
#include <commons/string.h>
#include "../include/init_cpu.h"
#include "../include/server.h"
#include <stdlib.h>
#include "../../shared/include/sockets.h"
#include "../../shared/include/manager.h"

#define SERVERNAME "CPU_SERVER"
t_log *logger;
int cpu_server;
int pid_actual = 0; // X
char *puerto;

#endif

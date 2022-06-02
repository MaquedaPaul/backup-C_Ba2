#ifndef KERNEL_MAIN_H_
#define KERNEL_MAIN_H_

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <commons/log.h>
#include <commons/string.h>
#include "../include/init_kernel.h"
#include "../include/cliente_cpu.h"
#include "server.h"
#include <stdlib.h>
#include "../../shared/include/sockets.h"
#include "../../shared/include/manager.h"

#define SERVERNAME "KERNEL_SERVER"
t_log *logger;
int kernel_server;
int pid_actual = 0;
char *puerto;
int fd_cpu_dispatch = 0;

#endif
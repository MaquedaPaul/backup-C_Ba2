#ifndef PLANIFICADOR_KERNEL_H
#define PLANIFICADOR_KERNEL_H

#include "../include/init_kernel.h"
t_list *procesosNuevos;
t_list *procesosReady;
t_list *procesosBlock;
t_list *procesosExec;
t_list *procesosSuspendedBlock;
t_list *procesosSuspendedReady;
t_list *procesosEnd;

pthread_t planificador_largo;
pthread_t planificador_mediano;
pthread_t planificador_corto;
int numero;

typedef struct
{
    t_PCB *unaPCB;
    bool estaSuspendido;
} t_proceso;

int cantidadProcesosEnMP();
int cantidadProcesosEnReady();
int cantidadProcesosEnBloqueado();
int cantidadProcesosEnEjecutando();
int cantidadProcesosEnUnaLista(t_list *unaLista);
#endif // PLANIFICADOR_KERNEL_H
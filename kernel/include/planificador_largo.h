#ifndef PLANIFICADOR_LARGO_H
#define PLANIFICADOR_LARGO_H
#include "../include/planificador.h"

int inicializarProceso(int fd);
t_proceso *crearNuevoProceso(t_PCB *PCB, bool estado);
void levantarHiloLargoPlazo();
void gestionarCambioLargoPlazo();
void ponerUnProcesoEnReady();
int addNuevoProceso(t_proceso *unProceso, t_list *unaLista);

#endif
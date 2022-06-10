#ifndef PLANIFICADOR_CORTO_H
#define PLANIFICADOR_CORTO_H
#include "../include/planificador.h"

void levantarHiloCortoPlazo();
void gestionarCambioCortoPlazo();

bool hayProcesosEnReady();

void ponerAEjecutarUnProceso();

void planificacionFIFO();

void planificacionSRT();

#endif // PLANIFICADOR_CORTO_H
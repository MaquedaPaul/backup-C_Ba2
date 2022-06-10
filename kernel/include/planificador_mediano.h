#ifndef PLANIFICADOR_MEDIANO_H
#define PLANIFICADOR_MEDIANO_H
#include "../include/planificador.h"

void levantarHiloMedianoPlazo();

void gestionarCambioMedianoPlazo();

bool superoElLimiteDeEspera();

void ponerEnSuspendidoBloqueadoUnProceso();

#endif // PLANIFICADOR_MEDIANO_H

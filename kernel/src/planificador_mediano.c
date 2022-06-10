#include "../include/planificador_mediano.h"

void levantarHiloMedianoPlazo()
{
    // pthread_create(planificador_mediano, NULL, (void *)gestionarCambioMedianoPlazo, NULL);
    //
    // hiloPlanificadorMedianoPlazo = true;
}

void gestionarCambioMedianoPlazo()
{
    while (1)
    {
        if (superoElLimiteDeEspera())
        {
            ponerEnSuspendidoBloqueadoUnProceso();
        }
    }
}

bool superoElLimiteDeEspera()
{
    return 0;
}

void ponerEnSuspendidoBloqueadoUnProceso()
{
}

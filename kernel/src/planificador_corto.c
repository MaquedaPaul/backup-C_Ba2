#include "../include/planificador_corto.h"

void ponerAEjecutarUnProceso()
{
    if (cfg->ALGORITMO_PLANIFICACION == "FIFO")
    {
        planificacionFIFO();
    }
    else if (cfg->ALGORITMO_PLANIFICACION == "SRT")
    {
        planificacionSRT();
    }
    else
    {
        log_error(logger_kernel, "Planificacion no reconocida");
    }
}

void planificacionFIFO()
{
    
}

void planificacionSRT()
{

}
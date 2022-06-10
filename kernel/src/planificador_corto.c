#include "../include/planificador_corto.h"

void levantarHiloCortoPlazo()
{
    // pthread_create(planificador_corto, NULL, (void *)gestionarCambioCortoPlazo, NULL);
    //  crear hilo con funcion gestionarCambioLargoPlazo
    //
    // hiloPlanificadorCortoLevantado = true;
}

void gestionarCambioCortoPlazo()
{
    while (1)
    {
        if (hayProcesosEnReady())
        {
            ponerAEjecutarUnProceso();
        }
    }
}

bool hayProcesosEnReady()
{
    return list_size(procesosReady) > 0;
}

void ponerAEjecutarUnProceso()
{
    if (cfg->ALGORITMO_PLANIFICACION == "FIFO")
    {
        /**
        pthread_t planificacion_corto;
                 pthread_create(&planificacion_corto, NULL, (void*) planificacionFIFO, NULL);
                 pthread_detach(planificacion_corto);
                 sem_post(&planificacionPausada); -> usa este semaforo para los 2 algoritmos
         **/
        planificacionFIFO();
    }
    else if (cfg->ALGORITMO_PLANIFICACION == "SRT")
    {
        /**
       pthread_t planificacion_corto;
                    pthread_create(&planificacion_corto, NULL, (void*) planificacionRR, NULL);
                    pthread_detach(planificacion_corto);
        **/
        planificacionSRT();
    }
    else
    {
        log_error(logger_kernel, "Planificacion no reconocida");
    }
}

void planificacionFIFO()
{ /**
    log_info(logger,"se inicio la planificacion FIFO");

    int ciclosTotales=0;
    int grado_multitarea = config_valores.multitarea;
    int ejecutando;
    int blockIO;
    int blockIOLoco;
    int tamanioReady;
    int tamanioReadyLoco;
    int sumaLoca;
    int block_sabotaje;
    int block_sabotajeLoco;
    int faltaPorArreglar=0;
    int posicionElegido=0;
    int globalExcec=0;
    int globalExcecLoco=0;

     **/
}

void planificacionSRT()
{
}
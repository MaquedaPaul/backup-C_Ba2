#include "../include/planificador_largo.h"

int inicializarProceso(int fd)
{

    // recv ---> de inicializarProceso
    // recibir lista de instrucciones y tamaño de un proceso
    // cliente_socket = PID
    // PAQUETE->unasInstrucciones
    // PAQUETE->processSize
    // PAQUETE->pc
    t_PCB *nuevaPCB = iniciar_pcb(cliente_socket, unasInstrucciones, processSize, cfg->estimacion);
    log_info(logger_kernel, "\n Se creo una PCB");
    if (!addNuevoProceso(nuevaPCB, procesosNuevos))
    {
        log_error(logger_kernel, "No se pudo aniadir un proceso a la lista de nuevos");
        return 1; // FAILURE
    }
    log_info(logger_kernel, "\n Se agrego exitosamente una PCB a la lista de nuevos");
    // retorna una PCB que almacenamos
    return 0; // EXITO
}

void levantarHiloLargoPlazo()
{
    // crear hilo con funcion gestionarCambioLargoPlazo
    //
}

void gestionarCambioLargoPlazo()
{
    while (1)
    {
        if (gradoMultiprogramacion < cantidadProcesosEnMP())
        {
            ponerAEjecutarUnProceso();
        }
    }
}

void finalizarProceso(t_PCB *unaPCB)
{
}
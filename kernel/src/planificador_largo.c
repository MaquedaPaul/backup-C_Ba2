#include "../include/planificador_largo.h"

int inicializarProceso(int fd)
{
    int cliente_socket;
    t_list *unasInstrucciones;
    int processSize;
    // recv ---> de inicializarProceso
    // recibir lista de instrucciones y tamaño de un proceso
    // cliente_socket = PID
    // PAQUETE->unasInstrucciones
    // PAQUETE->processSize
    // PAQUETE->pc
    t_PCB *nuevaPCB = iniciar_pcb(cliente_socket, unasInstrucciones, processSize, cfg->ESTIMACION_INICIAL);
    log_info(logger_kernel, "\n Se creo una PCB");
    t_proceso *nuevoProceso = crearNuevoProceso(nuevaPCB, false);

    if (!addNuevoProceso(nuevoProceso, procesosNuevos))
    {
        log_error(logger_kernel, "No se pudo agregar un proceso a la lista de nuevos");
        return 1; // FAILURE
    }
    log_info(logger_kernel, "\n Se agrego exitosamente una PCB a la lista de nuevos");
    // retorna una PCB que almacenamos
    return 0; // EXITO
}

t_proceso *crearNuevoProceso(t_PCB *PCB, bool estado)
{
    t_proceso *nuevoProceso = malloc(sizeof(t_proceso));
    nuevoProceso->unaPCB = PCB;
    nuevoProceso->estaSuspendido = estado;
    return nuevoProceso;
}

void levantarHiloLargoPlazo()
{

    // pthread_create(planificador_largo, NULL, (void *)gestionarCambioLargoPlazo, NULL);
    //  crear hilo con funcion gestionarCambioLargoPlazo
    //
    // hiloPlanificadorLargoLevantado = true;
}

void gestionarCambioLargoPlazo()
{
    int gradoMultiprogramacion = cfg->GRADO_MULTIPROGRAMACION;
    while (1)
    {
        if (gradoMultiprogramacion > cantidadProcesosEnMP())
        {
            ponerUnProcesoEnReady();
        }
    }
}

void ponerUnProcesoEnReady()
{
    cortarPrimerElementoDeUnaListaYPegarloEnOtra(procesosNuevos, procesosReady);
}

void finalizarProceso(t_proceso *unProceso)
{
}

int addNuevoProceso(t_proceso *unProceso, t_list *unaLista)
{
    return list_add(unaLista, unProceso);
}
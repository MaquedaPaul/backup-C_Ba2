#include "../include/planificador.h"

void addProceso(t_proceso *unProceso, t_list *unaLista)
{
    list_add(unaLista, unProceso);
}
void quitarProceso(t_proceso *unProceso, t_list *unaLista)
{
    // pendiente que cuando se destruya tiene que buscar el proceso en concreto
    //  poendiente destroy and destroy elements
    // list_remove_and_destroy(unaLista, unProceso);
}

int cantidadProcesosEnMP()
{
    return cantidadProcesosEnReady() + cantidadProcesosEnBloqueado() + cantidadProcesosEnEjecutando();
}

int cantidadProcesosEnReady()
{
    return cantidadProcesosEnUnaLista(procesosReady);
}
int cantidadProcesosEnBloqueado()
{
    return cantidadProcesosEnUnaLista(procesosBlock);
}
int cantidadProcesosEnEjecutando()
{
    return cantidadProcesosEnUnaLista(procesosExec);
}
int cantidadProcesosEnUnaLista(t_list *unaLista)
{
    return list_size(unaLista);
}

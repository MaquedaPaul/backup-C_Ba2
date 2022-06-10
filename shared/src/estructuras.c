#include "../include/estructuras.h"

void agregarInstruccionALista(t_list *lista, t_instruccion *unaInstruccion)
{
    if (!list_add(lista, unaInstruccion))
    {
        printf("Fallo al agregar una instruccion a la lista");
    }
}

void asignarPID(int pid, t_PCB *pcb)
{
    pcb->PID = pid;
}
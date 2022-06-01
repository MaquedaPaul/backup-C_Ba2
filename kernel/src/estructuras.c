#include "../include/estructuras.h"

static t_PCB *iniciar_pcb()
{
    // Inicializo en NULL para no tener basura
    // Debe asignarse valores distintos a estos.
    t_PCB *pcb = malloc(sizeof(t_PCB));
    pcb->PID = 0;
    pcb->instrucciones = NULL;
    pcb->program_counter = 0;
    pcb->estimacion_rafaga = 0.0f;
    return pcb;
}

void asignarPID(int pid, t_PCB *pcb)
{
    pcb->PID = pid;
}
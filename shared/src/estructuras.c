#include "../include/estructuras.h"

static t_PCB *iniciar_pcb(uint8_t unPID, t_list unasInstrucciones, uint64_t processSize, float estimacion)
{
    // Inicializo en NULL para no tener basura
    // Debe asignarse valores distintos a estos.

    t_PCB *pcb = malloc(sizeof(t_PCB));
    const int pc = 0;
    pcb->PID = unPID;
    log_info(logger_kernel, "Se cargo el PID %i", unPID);
    pcb->process_size = processSize;
    log_info(logger_kernel, "Se cargo el processSize %i", processSize);
    pcb->instrucciones = unasInstrucciones;
    log_info(logger_kernel, "Se cargaron las instrucciones");
    pcb->program_counter = pc;
    log_info(logger_kernel, "Se cargo el pc %i", pc);
    pcb->estimacion_rafaga = estimacion;
    log_info(logger_kernel, "Se cargo la estimacion %f", estimacion); // ERROR PQ NO ES FLOAT
    // falta direccion tabla de paginas.
    return pcb;
}

static t_instruccion *iniciar_instruccion(cod_instruccion unaInstruccion, uint32_t unCampo1, uint32_t unCampo2)
{
    t_instruccion *instruccion = malloc(sizeof(t_instruccion));
    instruccion->coi = unaInstruccion;
    instruccion->campo1 = unCampo1;
    instruccion->campo2 = unCampo2;
    return instruccion;
}
static t_list *iniciar_lista_instrucciones()
{
    t_list *listaInstrucciones = list_create();
    if (listaInstrucciones == NULL)
    {
        printf("No se pudo crear la lista");
        exit(2);
    }
    return listaInstrucciones;
}
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
#ifndef SHARED_ESTRUCTURAS_Ht_log
#define SHARED_ESTRUCTURAS_H
#include <commons/collections/list.h>
#include <inttypes.h> //tipos de int
#include <commons/log.h>
#include <commons/config.h>
#include <stdio.h>  //Printf y NULL
#include <stdlib.h> //exit
#define MAX_CONSOLES 100

// t_log *console_logger;
t_log *logger_kernel;
t_log *logger_cpu;
t_log *logger_memory;

bool hiloPlanificadorLargoLevantado;
bool hiloPlanificadorCortoLevantado;
bool hiloPlanificadorMedianoPlazoLevantado;

typedef enum
{
    NO_OP = 1,
    IO,
    READ,
    COPY,
    WRITE,
    EXIT = 6
} cod_instruccion;

typedef struct
{
    uint8_t PID;
    uint64_t process_size;
    t_list *instrucciones;
    uint16_t program_counter;
    float estimacion_rafaga;
} t_PCB;

typedef struct
{
    cod_instruccion coi;
    uint32_t campo1;
    uint32_t campo2;
} t_instruccion;

static t_PCB *iniciar_pcb(uint8_t unPID, t_list *unasInstrucciones, uint64_t processSize, float estimacion)
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
void agregarInstruccionALista(t_list *lista, t_instruccion *unaInstruccion);

int socketsConsola[MAX_CONSOLES];
void asignarPID(int pid, t_PCB *pcb);

#endif
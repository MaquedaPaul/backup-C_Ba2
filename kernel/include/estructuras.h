#ifndef KERNEL_ESTRUCTURAS_H
#define KERNEL_ESTRUCTURAS_H
#include <inttypes.h> //tipos de int
#include <commons/config.h>
#include <commons/collections/list.h>
#include <stdio.h>  //Printf y NULL
#include <stdlib.h> //exit
#define MAX_CONSOLES 100

typedef struct
{
    uint8_t PID;
    uint64_t process_size;
    t_list instrucciones;
    uint16_t program_counter;
    float estimacion_rafaga;
} t_PCB;
typedef struct
{
    char *nombre;
    uint32_t campo1;
    uint32_t campo2;
} t_instruccion;

static t_PCB *iniciar_pcb(uint8_t unPID, t_list unasInstrucciones,
                          uint64_t processSize, uint16_t pc, float estimacion);
static t_instruccion *iniciar_instruccion(char *instruccion, uint32_t campo1, uint32_t campo2);
static t_list *iniciar_lista_instrucciones();
void agregarInstruccionALista(t_list *lista, t_instruccion *unaInstruccion);

int socketsConsola[MAX_CONSOLES];
void asignarPID(int pid, t_PCB *pcb);

#endif
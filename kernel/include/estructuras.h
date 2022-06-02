#ifndef KERNEL_ESTRUCTURAS_H
#define KERNEL_ESTRUCTURAS_H
#include <inttypes.h> //tipos de int
#include <commons/list.h>
#define MAX_CONSOLES = 100;

typedef struct
{
    uint8_t PID;
    uint64_t process_size;
    lista_instrucciones instrucciones;
    uint16_t program_counter;
    float estimacion_rafaga;
} t_PCB;
typedef struct
{
    char *nombre;
    uint32_t campo1;
    uint32_t campo2;
} t_instruccion;

int socketsConsola[MAX_CONSOLES];
void asignarPID(int pid, t_PCB *pcb);

#endif
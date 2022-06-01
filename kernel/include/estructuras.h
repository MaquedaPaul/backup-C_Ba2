#ifndef KERNEL_ESTRUCTURAS_H
#define KERNEL_ESTRUCTURAS_H

typedef struct
{
    uint8_t PID;
    uint64_t process_size;
    lista_instrucciones instrucciones;
    uint16_t program_counter;
    float estimacion_rafaga;
} t_PCB;

#endif
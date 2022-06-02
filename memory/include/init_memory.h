#ifndef MEMORY_INIT_H
#define MEMORY_INIT_H
#define MODULENAME "MEMORY"
#include <fcntl.h>  //Para crear y abrir archivos "open"
#include <stdint.h> //Distintos tipos de INT
#include <stdio.h>  //Para incluir NULL
#include <stdlib.h> //Para malloc
#include <commons/config.h>
#include <commons/log.h>
#include <errno.h>                        //para errores
#include "../../shared/include/utils.h"   //para properties (has all)
#include "../../shared/include/manager.h" // para config y logger
#include <string.h>                       //para strdup
#include <unistd.h>                       // para close();
typedef struct
{
    uint32_t PUERTO_ESCUCHA;
    uint32_t TAM_MEMORIA;
    uint32_t TAM_PAGINA;
    uint32_t ENTRADAS_POR_TABLA;
    uint32_t RETARDO_MEMORIA;
    char *ALGORITMO_REEMPLAZO;
    uint32_t MARCOS_POR_PROCESO;
    uint32_t RETARDO_SWAP;
    char *PATH_SWAP;
} t_config_memory;

t_log *logger;
t_config_memory *cfg;
static t_config_memory *initialize_cfg()
// Inicializo en NULL para no tener basura
{
    t_config_memory *cfg = malloc(sizeof(t_config_memory));
    cfg->ALGORITMO_REEMPLAZO = NULL;
    cfg->PATH_SWAP = NULL;
    return cfg;
}
// Inicializa por el momento un logger y cfg
uint8_t init();

// Carga configuración del path indicado a una estructura t_config_memory, concretamente a cfg
uint8_t cargar_configuracion(char *path);
// Crea un archivo swap con el tamaño indicado en el path indicado
static bool crear_archivo_swap(char *path, uint32_t tamanio);

// Inicializa la memoria según archivo de cfg
uint8_t cargar_memoria();
// Libera todo el cfg con free y el logger
void cerrar_programa();
#endif
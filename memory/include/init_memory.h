#ifndef MEMORY_INIT_H
#define MEMORY_INIT_H

t_log *logger;
t_config_memory *cfg;

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

static t_config_mrhq *initialize_cfg() // Inicializo en NULL para no tener basura
{
    t_config_memory *cfg = malloc(sizeof(t_config_memory));
    cfg->ALGORITMO_REEMPLAZO = NULL;
    cfg->PATH_SWAP = NULL;
    return cfg;
}
#endif
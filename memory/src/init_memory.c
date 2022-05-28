#include "../include/init_memory.h"
// Declaro memoria y swap

void *swap;
void *memoria_principal;

uint8_t init()
{
    cfg = initialize_cfg(); // Inicializo la estructura que va a contener los datos del archivo memory.config
    logger = log_create("memory.log", MODULENAME, false, LOG_LEVEL_INFO);
    // Podría haber un semáforo para sincronizar....
    log_info(logger, "LOG 2");
    return 1;
}

uint8_t cargar_configuracion(char *path)
{
    t_config *cfg_file = config_create(path);

    if (cfg_file == NULL)
    {
        log_error(logger, "No se encontro memory.config");
        return 0;
    }
    char *properties[] = {
        "PUERTO_ESCUCHA",
        "TAM_MEMORIA",
        "TAM_PAGINA",
        "ENTRADAS_POR_TABLA",
        "RETARDO_MEMORIA",
        "ALGORITMO_REEMPLAZO",
        "MARCOS_POR_PROCESO",
        "RETARDO_SWAP",
        "PATH_SWAP",
        NULL};

    // Falta alguna propiedad
    if (!config_has_all_properties(cfg_file, properties))
    {
        log_error(logger, "Propiedades faltantes en el archivo de configuracion");
        config_destroy(cfg_file);
        return 0;
    }
    cfg->PUERTO_ESCUCHA = config_get_int_value(cfg_file, "PUERTO_ESCUCHA");
    cfg->TAM_MEMORIA = config_get_int_value(cfg_file, "TAMANIO_MEMORIA");
    cfg->TAM_PAGINA = config_get_int_value(cfg_file, "TAMANIO_PAGINA");
    cfg->ENTRADAS_POR_TABLA = config_get_int_value(cfg_file, "ENTRADAS_POR_TABLA");
    cfg->RETARDO_MEMORIA = config_get_int_value(cfg_file, "RETARDO_MEMORIA");
    cfg->ALGORITMO_REEMPLAZO = strdup(config_get_string_value(cfg_file, "ALGORITMO_REEMPLAZO"));

    cfg->MARCOS_POR_PROCESO = config_get_int_value(cfg_file, "MARCOS_POR_PROCESO");
    cfg->RETARDO_SWAP = config_get_int_value(cfg_file, "RETARDO_SWAP");
    cfg->PATH_SWAP = strdup(config_get_string_value(cfg_file, "PATH_SWAP"));

    log_info(logger, "Archivo de configuracion cargado correctamente");

    config_destroy(cfg_file);

    return 1;
}

static bool crear_archivo_swap(char *path, uint32_t tamanio)
{
    log_info(logger, "Creando SWAP en %s", path);
    // int open(const char *pathname, int flags, mode_t mode);
    int fd_swap = open(path, O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
    // O_RDWR: Archivo en modo escritura lectura
    // O_CREAT: Si no existe, crearlo en el path
    // S_IRUSR: El usuario cuenta con permisos para leer
    // S_IWUSR: El usuario cuenta con permisos para escribir

    if (fd_swap == -1)
    {
        log_error(logger, "No se pudo crear el area de SWAP. (errno %i)", errno);
        return false;
    }

    // Lógica del seteo en swap

    close(fd_swap);

    return true;
}

uint8_t cargar_memoria()
{
    memoria_principal = malloc(cfg->TAM_MEMORIA);
    if (memoria_principal == NULL)
    {
        log_error(logger, "No se pudo pedir memoria para memoria_principal");
        return 0;
    }
    // void *memset(void *str, int c, size_t n)
    // str ---> donde se va a llenar
    // c ---> el llenado de memoria principal se hace usando la conversión unsigned char del valor ingresado
    // n ---> Es el número de bytes para setear a memoria principal, por así decirlo el tam_maximo.
    // https://www.tutorialspoint.com/c_standard_library/c_function_memset.htm
    // Inicializo la memoria vacia (todo en 0)
    memset(memoria_principal, 0, cfg->TAM_MEMORIA);
    // pendiente más logica

    return 1;
}

void cerrar_programa()
{
    log_info(logger, "Finalizando el programa (...)");
    free(cfg->PUERTO_ESCUCHA);
    free(cfg->TAM_MEMORIA);
    free(cfg->TAM_PAGINA);
    free(cfg->ENTRADAS_POR_TABLA);
    free(cfg->RETARDO_MEMORIA);
    free(cfg->ALGORITMO_REEMPLAZO);
    free(cfg->MARCOS_POR_PROCESO);
    free(cfg->RETARDO_SWAP);
    free(cfg->ALGORITMO_REEMPLAZO);
    free(cfg->PATH_SWAP);
    free(cfg);
    free(logger);
}

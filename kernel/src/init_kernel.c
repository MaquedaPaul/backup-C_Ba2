#include "../include/init_kernel.h"

uint8_t init()
{

    cfg = initialize_cfg(); // Inicializo la estructura que va a contener los datos del archivo kernel.config
    logger = log_create("kernel.log", MODULENAME, false, LOG_LEVEL_INFO);
    // Podría haber un semáforo para sincronizar....

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
        "IP_MEMORIA",
        "PUERTO_MEMORIA",
        "IP_CPU",
        "PUERTO_CPU_DISPATCH",
        "PUERTO_CPU_INTERRUPT",
        "PUERTO_ESCUCHA",
        "ALGORITMO_PLANIFICACION",
        "ESTIMACION_INICIAL",
        "ALFA",
        "GRADO_MULTIPROGRAMACION",
        "TIEMPO_MAXIMO_BLOQUEADO",
        NULL};

    // Falta alguna propiedad
    if (!config_has_all_properties(cfg_file, properties))
    {
        log_error(logger, "Propiedades faltantes en el archivo de configuracion");
        config_destroy(cfg_file);
        return 0;
    }

    cfg->IP_MEMORIA = config_get_int_value(cfg_file, "IP_MEMORIA");
    // PENDIENTE
    // log_info(logger, "IP Cargada %s", ip);
    cfg->PUERTO_ESCUCHA = config_get_int_value(cfg_file, "PUERTO_ESCUCHA");
    cfg->IP_CPU = config_get_int_value(cfg_file, "IP_CPU");
    cfg->PUERTO_CPU_DISPATCH = config_get_int_value(cfg_file, "PUERTO_CPU_DISPATCH");
    cfg->PUERTO_CPU_INTERRUPT = config_get_int_value(cfg_file, "PUERTO_CPU_INTERRUPT");
    cfg->ALGORITMO_PLANIFICACION = strdup(config_get_string_value(cfg_file, "ALGORITMO_PLANIFICACION"));
    cfg->ESTIMACION_INICIAL = config_get_int_value(cfg_file, "ESTIMACION_INICIAL");
    cfg->ALFA = config_get_double_value(cfg_file, "ALFA");
    cfg->GRADO_MULTIPROGRAMACION = config_get_int_value(cfg_file, "GRADO_MULTIPROGRAMACION");
    cfg->TIEMPO_MAXIMO_BLOQUEADO = config_get_int_value(cfg_file, "TIEMPO_MAXIMO_BLOQUEADO");

    log_info(logger, "Archivo de configuracion cargado correctamente");

    config_destroy(cfg_file);

    return 1;
}
/*
void inicializar_servidor(int fd)
{
    char *puerto = string_itoa(cfg->PUERTO_ESCUCHA);
    log_info(logger, "Cargado puerto %s", puerto);
    *fd = iniciar_servidor(logger, SERVERNAME, "127.0.0.1", puerto);
    log_info(logger, "Iniciando servidor con la IP:PORT 127.0.0.1:%s", puerto);
}
*/
void cerrar_programa(t_log *logger)
{
    log_destroy(logger);
}

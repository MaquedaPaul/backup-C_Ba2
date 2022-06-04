#include "../include/init_console.h"

uint8_t init()
{

    cfg = initialize_cfg(); // Inicializo la estructura que va a contener los datos del archivo kernel.config
    logger = log_create("console.log", MODULENAME, false, LOG_LEVEL_INFO);
    // Podría haber un semáforo para sincronizar....

    return 1;
}

uint8_t cargar_configuracion(char *path)
{

    cfg_file = config_create(path);

    if (cfg_file == NULL)
    {
        log_error(logger, "No se encontro console.config");
        return 0;
    }

    char *properties[] = {
        "IP_KERNEL",
        "PUERTO_KERNEL",
        NULL};

    // Falta alguna propiedad
    if (!config_has_all_properties(cfg_file, properties))
    {
        log_error(logger, "Propiedades faltantes en el archivo de configuracion");
        config_destroy(cfg_file);
        return 0;
    }

    cfg->IP_KERNEL = strdup(config_get_string_value(cfg_file, "IP_KERNEL"));
    log_info(logger, "IP Cargada Correctamente: %s", cfg->IP_KERNEL);
    cfg->PUERTO_KERNEL = strdup(config_get_string_value(cfg_file, "PUERTO_KERNEL"));
    log_info(logger, "Puerto Cargado Correctamente: %s", cfg->PUERTO_KERNEL);
    log_info(logger, "Archivo de configuracion cargado correctamente");
    config_destroy(cfg_file);

    return 1;
}
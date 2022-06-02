#include "../include/init_cpu.h"

uint8_t init()
{

    cfg = initialize_cfg(); // Inicializo la estructura que va a contener los datos del archivo cpu.config
    logger = log_create("cpu.log", MODULENAME, false, LOG_LEVEL_INFO);
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
        "ENTRADAS_TLB",
        "REEMPLAZO_TLB",
        "RETARDO_NOOP",
        "IP_MEMORIA",
        "PUERTO_MEMORIA",
        "PUERTO_ESCUCHA_DISPATCH",
        "PUERTO_ESCUCHA_INTERRUPT",
        NULL};

    // Falta alguna propiedad
    if (!config_has_all_properties(cfg_file, properties))
    {
        log_error(logger, "Propiedades faltantes en el archivo de configuracion");
        config_destroy(cfg_file);
        return 0;
    }

    cfg->IP_MEMORIA = config_get_int_value(cfg_file, "IP_MEMORIA");
    cfg->ENTRADAS_TLB = config_get_int_value(cfg_file, "ENTRADAS_TLB");
    cfg->REEMPLAZO_TLB = strdup(config_get_string_value(cfg_file, "REEMPLAZO_TLB"));
    cfg->RETARDO_NOOP = config_get_int_value(cfg_file, "RETARDO_NOOP");
    cfg->PUERTO_MEMORIA = config_get_int_value(cfg_file, "PUERTO_MEMORIA");
    cfg->PUERTO_ESCUCHA_DISPATCH = config_get_int_value(cfg_file, "PUERTO_ESCUCHA_DISPATCH");
    cfg->PUERTO_ESCUCHA_INTERRUPT = config_get_int_value(cfg_file, "PUERTO_ESCUCHA_INTERRUPT");
    // PENDIENTE
    // log_info(logger, "IP Cargada %s", ip);

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

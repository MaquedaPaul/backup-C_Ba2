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
    cfg->PUERTO = config_get_int_value(cfg_file, "PUERTO");
    cfg->TAMANIO_MEMORIA = config_get_int_value(cfg_file, "TAMANIO_MEMORIA");
    cfg->TAMANIO_PAGINA = config_get_int_value(cfg_file, "TAMANIO_PAGINA");
    cfg->ENTRADAS_POR_TABLA = config_get_int_value(cfg_file, "ENTRADAS_POR_TABLA");
    cfg->RETARDO_MEMORIA = config_get_int_value(cfg_file, "RETARDO_MEMORIA");
    cfg->ALGORITMO_REEMPLAZO = strdup(config_get_string_value(cfg_file, "ALGORITMO_REEMPLAZO"));

    cfg->LRU = strcmp(cfg->ALGORITMO_REEMPLAZO, "LRU") == 0;

    cfg->MARCOS_POR_PROCESO = config_get_int_value(cfg_file, "MARCOS_POR_PROCESO");
    cfg->RETARDO_SWAP = config_get_int_value(cfg_file, "RETARDO_SWAP");
    cfg->PATH_SWAP = strdup(config_get_string_value(cfg_file, "PATH_SWAP"));

    log_info(logger, "Archivo de configuracion cargado correctamente");

    config_destroy(cfg_file);

    return 1;
}
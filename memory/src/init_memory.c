
// Declaro memoria y swap

void *swap;
void *memoria_principal;

uint8_t init()
{
    cfg = initialize_cfg();
    logger = log_create("memory.log", MODULENAME, false, LOG_LEVEL_INFO);
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
    cfg->TAMANIO_MEMORIA = config_get_int_value(cfg_file, "TAMANIO_MEMORIA");
    cfg->TAMANIO_PAGINA = config_get_int_value(cfg_file, "TAMANIO_PAGINA");
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

void cerrar_programa()
{
    log_info(logger, "Finalizando el programa (...)");
    free(cfg->PUERTO_ESCUCHA);
    free(cfg->TAMANIO_MEMORIA);
    free(cfg->TAMANIO_PAGINA);
    free(cfg->ENTRADAS_POR_TABLA);
    free(cfg->RETARDO_MEMORIA);
    free(cfg->ALGORITMO_REEMPLAZO);
    free(cfg->MARCOS_POR_PROCESO);
    free(cfg->RETARDO_SWAP);
    free(cfg->ALGORITMO_REEMPLAZO);
    free(cfg->PATH_SWAP);
    free(cfg);
}

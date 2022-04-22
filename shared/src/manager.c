t_config *iniciar_config(char *path)
{
    t_config *nuevo_config;

    nuevo_config = config_create(path);

    if (nuevo_config == NULL)
    {
        printf("No se pudo leer la config\n");
        exit(2);
    }

    return nuevo_config;
}

void terminar_programa(int conexion, t_log *logger, t_config *config)
{
    /* Y por ultimo, hay que liberar lo que utilizamos (conexion, log y config)
      con las funciones de las commons y del TP mencionadas en el enunciado */
    if (logger != NULL)
    {
        log_destroy(logger);
    }

    if (config != NULL)
    {
        config_destroy(config);
    }

    liberar_conexion(conexion);
}

t_log *iniciar_logger(char *path, char *name, int debug, int log_level)
{
    t_log *nuevo_logger;
    if (log_level > 5 || log_level < 0)
    {
        printf("log level invalid");
        return exit(1);
    }
    if (debug != 0 || debug != 1)
    {
        printf("debug invalid");
        return exit(1);
    }
    nuevo_logger = log_create(path, name, debug, log_level);

    if (nuevo_logger == NULL)
    {
        printf("No se pudo crear el logger\n");
        exit(1);
    }
    return nuevo_config;
}
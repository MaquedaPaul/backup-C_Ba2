#include "include/main.h"
extern t_config_memory *cfg;
extern t_log *logger;
extern void *memoria_principal;
extern void *swap;
int memory_server;

int main()
{
    printf("prueba");
    t_log *logger2;
    logger2 = log_create("memory.log", MODULENAME, false, LOG_LEVEL_INFO);
    log_info(logger2, "PRUEBA");
    if (!init() || !cargar_configuracion("memory.config") || !cargar_memoria()) // cada función va a hacer su operación, si las tres fallan, se cierra la app
    {
        cerrar_programa();
        return EXIT_FAILURE;
    }

    // ****** CREACION DEL SERVIDOR ******

    char *puerto = string_itoa(cfg->PUERTO_ESCUCHA);
    log_info(logger, "Cargado puerto %s", puerto);
    memory_server = iniciar_servidor(logger, SERVERNAME, "0.0.0.0", puerto);
    log_info(logger, "Iniciando servidor con la IP:PORT 0.0.0.0:%s", puerto);
    free(puerto);

    //****** ESCUCHANDO ******
    log_info(logger, "Escuchando por cliente %s", puerto);
    while (server_escuchar(SERVERNAME, memory_server))
        ;

    liberar_conexion(&memory_server);
    cerrar_programa();
    return EXIT_SUCCESS;
}
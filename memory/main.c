
#include "include/main.h"
extern t_config_memory *cfg;
extern t_log *logger;
extern void *memoria_principal;
extern void *swap;
int memory_server;

int main()
{
    if (!init() || !cargar_configuracion("memory.config") || !cargar_memoria()) // cada función va a hacer su operación, si las tres fallan, se cierra la app
    {
        cerrar_programa();
        return EXIT_FAILURE;
    }

    // ****** CREACION DEL SERVIDOR ******
    char *puerto = string_itoa(cfg->PUERTO_ESCUCHA);
    memory_server = iniciar_servidor(logger, SERVERNAME, "0.0.0.0", puerto);
    free(puerto);

    //****** ESCUCHANDO ******
    while (server_escuchar(SERVERNAME, memory_server));

    liberar_conexion(&memory_server);
    cerrar_programa();
    return EXIT_SUCCESS;

#include "include/main.h"

// Conexiones
// Kernel

int main()
{
    t_log *logger2;
    printf("prueba\n");
    logger2 = log_create("cpu.log", MODULENAME, false, LOG_LEVEL_INFO);
    log_info(logger2, "PRUEBA");
    printf("hola\n");

    if (!init() || !cargar_configuracion("cpu.config"))
    // cada función va a hacer su operación, si las tres fallan, se cierra la app
    {
        cerrar_programa(logger2);
        return EXIT_FAILURE;
    }

    // signal(SIGINT, sighandler); // Para poder cerrar correctamente el programa apretando CTRL + C
    logger = log_create("cpu.log", "CPU", true, LOG_LEVEL_INFO);

    // ****** CREACION DEL SERVIDOR ******

    char *puerto = string_itoa(cfg->PUERTO_ESCUCHA_DISPATCH);
    // char *ip = string_itoa("127.0.0.1");
    log_info(logger, "Cargado puerto %s", puerto);
    cpu_server = iniciar_servidor(logger, SERVERNAME, "127.0.0.1", puerto);
    log_info(logger, "Iniciando servidor con la IP:PORT 127.0.0.1:%s", puerto);

    while (server_escuchar(logger, SERVERNAME, cpu_server))
        ;
    liberar_conexion(cpu_server);
    cerrar_programa(logger);

    return 0;
}

// RECIBE PCB DE KERNEL
// Definir struct de PCB
// typedef struct
//{
//    int ID;
//    int SIZE;
//    instruccion[] LISTA_INSTRUCCIONES;
//    int PC; // Program counter
//    TABLA_PAGINAS;
//    ESTIMACION_RAFAGA;
//} PCB;
//
// enum instruccion
//{
//    TipoInstruccion tipo;
//    int tiempo;
//    int dir_logica1;
//    int dir_logica2;
//    int valor;
//}intruccion;
//
//// Averiguar tipos
//
//// Ciclo de Instruccion
// while (TRUE)
//{
//     // averiguar condicion
//     void fetch()
//     {
//         // Busca instruccion indicada por el PC en el PCB
//         instruccion = pcb.LISTA_INSTRUCCIONES[pcb.PC];
//         // Actualiza PC (pasa al siguiente?)
//     }
//
//     void decode()
//     {
//         // interpreta la instruccion a ejecutar
//         // si es COPY, ocurre fetch operands(como se si es COPY?)
//         if (instruccion == COPY)
//         {
//             valor = fetch_operands(dir_Memoria);
//         }
//     }
//
//     void fetch_operands(dir_Memoria)
//     {
//         // busca el valor de memoria de la dir logica dada
//     }
//
//     void execute(instruccion)
//     {
//         check_interrupt();
//         // Ejecuta la instruccion dependiendo de lo que sea
//         switch (instruccion.tipo)
//         {
//         case NO_OP:
//             // Esperar un tiempo determinado por un archivo de config(como obtengo el tiempo del archivo?)
//         case I / O:
//             // Bloquea y devuelve el PCB al kernel junto con el tiempo de bloqueo
//         case EXIT:
//             // Proceso finalizado, devuelve PCB
//         }
//
//         // actualiza PC despues de terminar
//         pcb.PC = pcb.PC++;
//     }
//
//     void check_interrupt()
//     {
//         // mira si llego una interrupcion
//         if (hay interrupcion)
//         {
//             return PCB
//         }
//         // si si, devuelve el PCB actualizado(dispatch)
//         // si no, reinicia el ciclo
//     }
//
//     NoOp()
//     {
//     }
//
//     EXIT()
//     {
//     }
//
//     IO()
//     {
//     }
//
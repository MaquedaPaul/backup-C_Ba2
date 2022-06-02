#include "include/main.h"

// Conexiones
// Kernel

static void procesar_conexion(void *void_args)
{
    t_procesar_conexion_args *args = (t_procesar_conexion_args *)void_args;
    t_log *logger = args->log;
    int cliente_socket = args->fd;
    char *server_name = args->server_name;
    free(args);

    op_code cop;
    while (cliente_socket != -1)
    {

        if (recv(cliente_socket, &cop, sizeof(op_code), 0) != sizeof(op_code))
        {
            log_info(logger, "DISCONNECT!");
            return;
        }

        switch (cop)
        {

        case HANDSHAKE:
        {
            uint32_t apreton;

            if (!recvHandShake(cliente_socket, &apreton))
            {
                log_error(logger, "Fallo recibiendo HANDSHAKE");
                break;
            }
            printf("Handshake recibido, %i", apreton);
        }

            /*
                    case NO_OP:
                    {
                        uint32_t cantidad;

                        if (!recv_uint32_t(cliente_socket, &cantidad))
                        {
                            log_error(logger, "Fallo recibiendo NO_OP");
                            break;
                        }

                        log_info(logger, "Tengo que hacer %u operaciones de NO_OP ", cantidad);
                        break;
                    }

                    case IO:
                    {
                        uint32_t tiempo;
                        if (!recv_uint32_t(cliente_socket, &tiempo))
                        {
                            log_error(logger, "Fallo recibiendo IO");
                            break;
                        }

                        log_info(logger, "Me debo bloquear por %u  milisegundos", tiempo);
                        break;
                    }

                    case READ:
                    {

                        uint32_t direccion_logica;
                        if (!recv_uint32_t(cliente_socket, &direccion_logica))
                        {
                            log_error(logger, "Fallo recibiendo READ");
                            break;
                        }
                        log_info(logger, "Debo leer el valor de memoria correspondiente a la dir %u y luego imprimirlo por pantalla", direccion_logica);
                        break;
                    }

                    case WRITE:
                    {
                        uint32_t direccion_logica;
                        uint32_t valor;
                        if (!recv_dos_uint32_t(cliente_socket, &direccion_logica, &valor))
                        {
                            log_error(logger, "Fallo recibiendo WRITE");
                            break;
                        }
                        log_info(logger, "Debo escribir en memoria el valor %u en el espacio %u", valor, direccion_logica);
                        break;
                    }

                    case COPY:
                    {
                        uint32_t direccion_logica_destino;
                        uint32_t direccion_logica_origen;
                        if (!recv_dos_uint32_t(cliente_socket, &direccion_logica_destino, &direccion_logica_origen))
                        {
                            log_error(logger, "Fallo recibiendo COPY");
                            break;
                        }
                        log_info(logger, "Debo escribir en %u el valor contenido dentro de %u", direccion_logica_destino, direccion_logica_origen);
                        break;
                    }

                    case EXIT:
                        log_info(logger, "EXIT");
                        break;
            */
        // Errores
        case -1:
            log_error(logger, "Cliente desconectado de %s...", server_name);
            return;
        default:
            log_error(logger, "Algo anduvo mal en el server de %s", server_name);
            log_info(logger, "Cop: %d", cop);
            return;
        }
    }

    log_warning(logger, "El cliente se desconecto de %s server", server_name);
    return;
}

int server_escuchar(t_log *logger, char *server_name, int server_socket)
{
    int cliente_socket = esperar_cliente(logger, server_name, server_socket);

    if (cliente_socket != -1)
    {
        pthread_t hilo;
        t_procesar_conexion_args *args = malloc(sizeof(t_procesar_conexion_args));
        args->log = logger;
        args->fd = cliente_socket;
        args->server_name = server_name;
        pthread_create(&hilo, NULL, (void *)procesar_conexion, (void *)args);
        pthread_detach(hilo);
        return 1;
    }
    return 0;
}

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

    while (server_escuchar_cpu(logger, SERVERNAME, cpu_server))
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
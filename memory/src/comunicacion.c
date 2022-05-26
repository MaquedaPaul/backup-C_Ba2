#include "include/comunicacion.h"
/*
Inicialización del proceso
El módulo deberá crear las estructuras administrativas necesarias y enviar como respuesta el número de tabla de página de primer nivel de ese proceso.

*/
typedef struct
{
    int fd;
    char *server_name;
} t_procesar_conexion;

int iniciarProceso(int proceso)
{
    // crear estructuras administrativas
    // obtenerPrimerNivelProceso(); ---> probablemente se consiga cuando se
    // creen las estructuras administrativas
    int primerNivelProceso = obtenerPrimerNivelProceso();
    return primerNivelProceso;
};

/*
Suspensión de proceso
Al ser suspendido un proceso, se debe liberar su espacio en memoria, escribiendo en SWAP solamente la información necesaria. Se debe tener en cuenta que, para la realización de este trabajo práctico, no se requiere el swapeo de tablas de páginas.
*/
void suspenderProceso(int proceso)
{
    escribirEnSWAP(proceso); // solamente informacion necesaria
    liberarMemoria(proceso);
};

/*
Finalización de proceso
Al ser finalizado un proceso, se debe liberar su espacio de memoria y eliminar su archivo de SWAP correspondiente. Se debe tener en cuenta que, para la realización de este trabajo, no es requerido eliminar las tablas de páginas del proceso.

*/
void finalizarProceso(int proceso)
{
    liberarMemoria(proceso);
    eliminarSWAP(proceso); // no se eliminan las tablas de páginas del proceso,
    // o no apriori
};

/*
Acceso a tabla de páginas
El módulo deberá responder lo siguiente:
Si se trata de una tabla de primer nivel, el número de la tabla de segundo nivel.
Si se trata de una tabla de segundo nivel, el número de marco correspondiente. Para este caso, si la página correspondiente no se encuentra en memoria (bit de presencia en 0) se deberá cargar la misma en algún marco para poder finalmente responderle a la CPU. Téngase en cuenta que esto podría incluir reemplazos de páginas y escrituras en swap.

*/
void accesoATablaDePaginas()
{
}

void cargarEnMarco(int tabla)
{
    // remplazos de paginas
    // escritura en swap
}

/*
Acceso a espacio de usuario
El módulo deberá realizar lo siguiente:
Ante un pedido de lectura, devolver el valor que se encuentra en la posición pedida
Ante un pedido de escritura, escribir lo indicado en la posición pedida. En caso satisfactorio se responderá un mensaje de ‘OK’ o, de lo contrario, un mensaje de error.
*/
void accesoAEspacioUsuario(int tipoPedido, int posicion)
{
    switch (tipoPedido)
    {
    case LECTURA:
        return valorEnPosicion(posicion);
    case ESCRITURA:
        if (escribirEn(posicion) == 0)
        {
            fallar("No se pudo escribir en la posicion %d porque...", posicion);
        }
        log("Se escribrio correctamente en la posicion %d", posicion);
        break;
    default:
        fallar("No se reconoce el tipo de pedido %d", tipoPedido);
        break;
    }
}

static void procesar_conexion(void *void_args)
{
    t_procesar_conexion *args = (t_procesar_conexion *)void_args;
    int cliente_socket = args->fd;
    char *server_name = args->server_name;
    // Obtengo los datos de la conexión recibida por parámetro
    free(args);
    // Libero estructura auxiliar

    op_code cop;
    // Según el código de operación voy a mandar x o y mensaje
    while (cliente_socket != -1)
    {

        // ssize_t recv(int socket, void *buffer, size_t length, int flags);
        // flags=0 ---> MSG_PEEK
        /*Peeks at an incoming message. The data is treated as unread and the next recv() or similar function shall still return this data.
         */
        if (recv(cliente_socket, &cop, sizeof(op_code), 0) != sizeof(op_code))
        {
            log_info(logger, "Desconectando el cliente"));
            return;
        }

        switch (cop)
        {

        case START_PROCESS:
        {
            // Inicializar estructuras necesarias
            //* Un espacio contiguo de memoria (representado por un void*). Este representará el espacio de usuario de la misma, donde los procesos podrán leer y/o escribir. (como está planteado ahora, ya está inicializado siempre, pero quizás convendria incializarla a partir de acá)
            /*if (!initialize_memory){
                log_info(logger, "Inicializando memoria");
                //Verificar si se inicializó bien sino retornar.
            }
            */
            // Las tablas de páginas, que representarán el espacio de Kernel.
            /*if (!initialize_table_pages){
              log_info(logger, "Inicializando tabla de páginas");
              //Verificar si se inicializó bien sino retornar.
          }
          */
            // Una vez que se inicializa mp y tabla de paginas, guardo la variable con la info
            // de las tablas de paginas y la utilizo en la función:
            colocar_pagina_en_mp();
            // Un archivo por proceso, que representarán el espacio de SWAP de cada uno.
            crear_swap();
            // Es responsabilidad de la memoria conocer el proceso que se está creando?
            // Cuando finalizo un proceso, qué necesito que me pasen? la página y desplazamiento?
            break;
        }

        case SUSPEND_PROCESS:
        {
            int proceso;
            escribirEnSWAP(proceso);
            liberarMemoria(proceso);
            break;
        }

        case END_PROCESS:
        {
            int proceso;
            liberarMemoria(proceso);
            eliminarSWAP(proceso);
            break;
        }

        case ACCESS_TO_TABLE_PAGES:
        {
            // No intuyo parametros ni tipo de dato
            int tabla;
            tabla = acceso();
            if (tabla == PRIMER_NIVEL)
            {
                return segundoNivel(tabla);
            }
            else if (tabla == SEGUNDO_NIVEL)
            {
                if (bitPresencia(tabla) == 0)
                {
                    if (cargarEnMarco(tabla) != 1)
                    {
                        fallar("No se pudo cargar la tabla en un marco");
                    }
                }
                return marco(tabla);
            }
            else
            {
                fallar("Tabla no reconocida");
            }
            break;
        }

        case ACCESS_TO_USER_SPACE_READ:
        {
            return valorEnPosicion(posicion);
        }
        case ACCESS_TO_USER_SPACE_WRITE:
        {
            if (escribirEn(posicion) == 0)
            {
                fallar("No se pudo escribir en la posicion %d porque...", posicion);
                break;
            }
            log("Se escribrio correctamente en la posicion %d", posicion);
            break;
        }

        // Errores
        case -1:
            log_error(logger, "Cliente desconectado de Memory...");
            return;
        default:
            log_error(logger, "Algo anduvo mal en el server de la Memory");
            return;
        }
    }
    log_warning(logger, "El cliente se desconecto de %s server", server_name);
    return;
}

int server_escuchar(char *server_name, int server_socket)
{
    int cliente_socket = esperar_cliente(logger, server_name, server_socket);

    if (cliente_socket != -1)
    {
        pthread_t hilo;
        t_procesar_conexion *args = malloc(sizeof(t_procesar_conexion_args));
        args->fd = cliente_socket;
        args->server_name = server_name;
        pthread_create(&hilo, NULL, (void *)procesar_conexion, (void *)args);
        // Poner en funcionamiento el hilo
        pthread_detach(hilo);
        return 1;
    }
    return 0;
}

#include "include/main.h"

bool flag = 0;
uint32_t msgFin = 100;
uint32_t handshake = 5;
int main()
{

    if (!init() || !cargar_configuracion("console.config"))
    {
        // cerrar_programa(logger2); --> implementar
        return EXIT_FAILURE;
    }

    // PENDIENTE ¿SEMÁFORO?
    if (!generar_conexiones(logger, &fd_kernel))
    {
        log_error(logger, "No se pudo conectar con Kernel, cerrando consola\n");
        printf("No se pudo conectar con Kernel, cerrando consola\n");
        return EXIT_FAILURE;
    }

    /*
     while (!)
     {
         if (flag != 1)
         {
             printf("Intentando conectarse con kernel");
             flag = 1;
         }
     }
 */

    sendHandShake(fd_kernel, handshake);

    // PENDIENTE SEMAFORO
    op_code esperar_finalizacion;
    op_code cop;

    if (recv(fd_kernel, &cop, sizeof(op_code), 0) != sizeof(op_code))
    {
        log_error(logger, "Fallo recibiendo codigo de handshake");
        return EXIT_FAILURE;
    }
    if (cop == HANDSHAKE)
    {
        if (!recvHandShake(fd_kernel, &esperar_finalizacion))
        {
            log_error(logger, "Fallo recibiendo finalizacion\n");
        }

        if (esperar_finalizacion == END_PROCESS)
        {
            log_info(logger, "Finalizando consola exitosamente");
            return EXIT_SUCCESS;
        }
    }
    else
    {
        log_error(logger, "Codigo no reconocido %i", esperar_finalizacion);
    }

    // cerrar_programa(logger);
    return EXIT_SUCCESS;
}

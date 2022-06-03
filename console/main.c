#include "include/main.h"

bool flag = 0;

int main()
{

    t_log *logger = log_create("console.log", "CONSOLE", true, LOG_LEVEL_INFO);

    int fd_kernel = 0; // fd significa file descriptor. Es el socket
    // PENDIENTE ¿SEMÁFORO?
    while (!generar_conexiones(logger, &fd_kernel))
    {
        if (flag != 1)
        {
            printf("Intentando conectarse con kernel");
            flag = 1;
        }
    }
    uint32_t msgFin = 1;
    uint32_t handshake = 5;
    sendHandShake(fd_kernel, handshake);
    // PENDIENTE SEMAFORO
    uint32_t esperar_finalizacion;
    log_error(logger, "%i", esperar_finalizacion);
    // reintentar:
    if (!recvHandShake(fd_kernel, &esperar_finalizacion))
    {
        log_error(logger, "Fallo recibiendo HANDSHAKE");
    }
    printf("\n");
    log_error(logger, "%i", esperar_finalizacion);
    if (esperar_finalizacion == msgFin)
    {

        return EXIT_SUCCESS;
    }
    else
    {
        printf("\n");
        log_error(logger, "%i", esperar_finalizacion);
        printf("No me tengo que finalizar pero la re paja asi que chau.");
        // goto reintentar;
    }

    // FILE *flujo = fopen("ejemplo.txt","r");
    // 	if(flujo == NULL){
    // 		perror("Error en la apertura del archivo txt");
    // 		return 1;
    // 	}

    // while(feof(flujo) == 0){ //feof me devuelve !=0 si el flujo no esta vacio
    // }

    /*
        int a;

        scanf("%d", &a);
        send_uint32_t(fd_kernel, 5, NO_OP);

        scanf("%d", &a);

        send_uint32_t(fd_kernel, 3000, IO);

        scanf("%d", &a);
        send_dos_uint32_t(fd_kernel, 4, 42, WRITE);

        scanf("%d", &a);
        */
    cerrar_programa(logger);
    return EXIT_SUCCESS;
}

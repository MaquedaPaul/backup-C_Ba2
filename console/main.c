#include "include/main.h"

int main()
{

    t_log *logger = log_create("console.log", "CONSOLE", true, LOG_LEVEL_INFO);

    int fd_kernel = 0; // fd significa file descriptor. Es el socket
    if (!generar_conexiones(logger, &fd_kernel))
    {
        cerrar_programa(logger);
        return EXIT_FAILURE;
    }

    // FILE *flujo = fopen("ejemplo.txt","r");
    // 	if(flujo == NULL){
    // 		perror("Error en la apertura del archivo txt");
    // 		return 1;
    // 	}

    // while(feof(flujo) == 0){ //feof me devuelve !=0 si el flujo no esta vacio
    // }
    uint32_t handshake = 5;
    sendHandShake(fd_kernel, handshake);
    int a;

    scanf("%d", &a);
    send_uint32_t(fd_kernel, 5, NO_OP);

    scanf("%d", &a);

    send_uint32_t(fd_kernel, 3000, IO);

    scanf("%d", &a);
    send_dos_uint32_t(fd_kernel, 4, 42, WRITE);

    scanf("%d", &a);
    cerrar_programa(logger);
    return EXIT_SUCCESS;
}

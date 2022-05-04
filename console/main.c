#include "include/main.h"

int main() {

    t_log* logger = log_create("console.log", "CONSOLE", true, LOG_LEVEL_INFO);

    int fd_kernel=0;
    if (!generar_conexiones(logger,&fd_kernel)) {
        cerrar_programa(logger);
        return EXIT_FAILURE;
    }

    int a;

    scanf("%d", &a);
    send_mirar_netflix(fd_kernel, "Inception", 14);

    //scanf("%d", &a);
    //send_aprobar_operativos(fd_mod3, 7, 8);

    scanf("%d", &a);
    cerrar_programa(logger);
    return EXIT_SUCCESS;
}

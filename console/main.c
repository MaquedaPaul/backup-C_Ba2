#include "include/main.h"

int main()
{
    t_log *logger = log_create("console.log", "CONSOLE", true, LOG_LEVEL_INFO);

    int fd_kernel = 0; // fd_cpu = 0; //fd: file descriptor

    if (!generar_conexiones(logger, &fd_kernel))
    {
        cerrar_programa(logger);
        return EXIT_FAILURE;
    }

    int a;

    scanf("%d", &a);
    send_string_and_number_phrase(fd_kernel, "A phrase", 14);

    // scanf("%d", &a);
    // send_twoNumbers(fd_cpu, 7, 8);

    scanf("%d", &a);
    cerrar_programa(logger);
    return EXIT_SUCCESS;
}
<<<<<<< HEAD
#include "include/main.h"

//Conexiones
//Kernel
bool generar_conexiones(t_log *logger, int *fd_kernel)
{
    // No hardcodear, levantar de config
    char *ip_kernel;
    char *puerto_kernel;

    t_config *configKernelConnection = iniciar_config("./kernel.config");
    ip_kernel = config_get_string_value(configKernelConnection, "IP_KERNEL");
    log_info(logger, "IP Cargada %s", ip_kernel);
    puerto_kernel = config_get_string_value(configKernelConnection, "PUERTO_KERNEL");
    log_info(logger, "Puerto Cargado %s", puerto_kernel);

    // char *port_kernel = "6969";
    //  char *port_mod3 = "4200";
    // char *ip_kernel = "0.0.0.0";
    //  char *ip_mod3 = "0.0.0.0";

    *fd_kernel = crear_conexion(logger,"KERNEL",ip_kernel, puerto_kernel); // es el que acopla, pero antes te tienen que estar esperando

    return *fd_kernel != 0; //&& *fd_cpu != 0;
}



//RECIBE PCB DE KERNEL
//Definir struct de PCB
typedef struct{
    int ID; 
    int SIZE;
    instruccion[] LISTA_INSTRUCCIONES;
    int PC; //Program counter
    TABLA_PAGINAS; 
    ESTIMACION_RAFAGA; 
}PCB;

enum instruccion{
TipoInstruccion tipo;
int tiempo;
int dir_logica1;
int dir_logica2;
int valor;
}intruccion;


//Averiguar tipos

//Ciclo de Instruccion
while(TRUE){
    //averiguar condicion
    void fetch(){
        //Busca instruccion indicada por el PC en el PCB
        instruccion = pcb.LISTA_INSTRUCCIONES[pcb.PC];
        //Actualiza PC (pasa al siguiente?)
        
    }

    void decode(){
        //interpreta la instruccion a ejecutar
        //si es COPY, ocurre fetch operands(como se si es COPY?)
        if(instruccion == COPY){
            valor = fetch_operands(dir_Memoria);
        }
    }

    void fetch_operands(dir_Memoria){
        //busca el valor de memoria de la dir logica dada

    }

    void execute(instruccion){
        check_interrupt();
        //Ejecuta la instruccion dependiendo de lo que sea
        switch (instruccion.tipo){
            case NO_OP:
                //Esperar un tiempo determinado por un archivo de config(como obtengo el tiempo del archivo?)
            case I/O:
                //Bloquea y devuelve el PCB al kernel junto con el tiempo de bloqueo
            case EXIT:
                //Proceso finalizado, devuelve PCB
        
        }
        
        
        //actualiza PC despues de terminar
        pcb.PC = pcb.PC++;
    }

    void check_interrupt(){
        //mira si llego una interrupcion
        if(hay interrupcion){
            return PCB
        }
        //si si, devuelve el PCB actualizado(dispatch)
        //si no, reinicia el ciclo

    }

    NoOp(){

    }

    EXIT(){

    }

    IO(){

    }


=======
#include "include/main.h"

int main()
{
    return 0;
>>>>>>> 4c0860d7e02a71df3a3f902599ec0cf3b7d1104a
}
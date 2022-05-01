/*
Como se mencionó anteriormente el submódulo de SWAP va a ser el encargado dentro de la memoria de manejar las peticiones de lectura y escritura en SWAP.
Los archivos de SWAP se van a ir generando a medida que se carguen los diferentes procesos en la memoria y cuyo nombre va a constar del PID del proceso y una extensión la cual vamos a llamar .swap, quedando de esta forma por ejemplo los archivos 1.swap, 2.swap, 3.swap correspondiendo a los procesos con PID 1, 2 y 3. Al finalizar un proceso, se deberá eliminar su archivo de swap asignado.
*/

void manejarPeticionLecturaEnSWAP(int peticion)
{
    retardo(config);
}
void manejarPeticionEscrituraEnSWAP()
{
    retardo(config);
}
void generarArchivoSWAP(int PID)
{
    crearArchivo("PID.swap");
}

void eliminarArchivoSWAP(int PID)
{
    eliminarArchivo("PID.swap");
}

/*
El SWAP, al imitar los accesos a disco, deberá implementarse como si fuera un único hilo de ejecución.Esto significa que no se podrán tener 2 o más lecturas / escrituras en paralelo.Y, para que la simulación tenga más sentido con la realidad y la diferencia de velocidades existente entre la memoria RAM y el disco, cada acceso a SWAP deberá tener una espera en milisegundos la cual estará definida por archivo de configuración a modo de retardo de swap.
*/
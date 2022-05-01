/*
Inicialización del proceso
El módulo deberá crear las estructuras administrativas necesarias y enviar como respuesta el número de tabla de página de primer nivel de ese proceso.

*/

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
{ // No intuyo parametros ni tipo de dato
    int tabla;
    tabla = acceso();
    if (tabla == PRIMER_NIVEL)
    {
        return tabla.segundoNivel(); // modo objetoso xd, en adelante MO
    }
    else if (tabla == SEGUNDO_NIVEL)
    {
        if (tabla.bitPresencia() == 0)
        { // MO
            if (cargarEnMarco(tabla) != 1)
            {
                fallar("No se pudo cargar la tabla en un marco");
            }
        }
        return tabla.marco(); // MO
    }
    else
    {
        fallar("Tabla no reconocida");
    }
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
        fallar("No se reconocce el tipo de pedido %d", tipoPedido);
        break;
    }
}

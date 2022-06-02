/*
Esquema de memoria
La asignación de memoria de este trabajo práctico utilizará un esquema de paginación jerárquica de dos niveles, donde las tablas de ambos niveles contarán con la misma cantidad de entradas, definida por archivo de configuración. La tabla de primer nivel estará compuesta por referencias a las tablas de páginas de segundo nivel, como se muestra en el siguiente gráfico.

*/

// se me ocurre que deberían ser dos listas enlazadas
int paginacionNivelUno(int cantidadEntradas, int referenciasASegundoNivel);
int paginacionNivelDos(int cantidadEntradas, int asignacionDeMarcosFija, int scopeDeReemplazoLocal, int algoritmoReemplazo);

/*
Además debe implementar memoria virtual, más específicamente, paginación bajo demanda. En este contexto, se definirá una asignación de cantidad de marcos fija definida por archivo de configuración y un scope de reemplazo local. El algoritmo de reemplazo será definido por archivo de configuración, pudiendo ser Clock o Clock Modificado.

*/
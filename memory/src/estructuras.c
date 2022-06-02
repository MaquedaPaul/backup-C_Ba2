/*
La memoria contará principalmente con 3 estructuras:
Un espacio contiguo de memoria (representado por un void*). Este representará el espacio de usuario de la misma, donde los procesos podrán leer y/o escribir.
Las tablas de páginas, que representarán el espacio de Kernel.
Un archivo por proceso, que representarán el espacio de SWAP de cada uno.

*/

void *espacioContiguo(); // usuarios---> leen y escriben

// tipo de dato void por el momento.
void tablasDePaginas(); // representa el espacio de kernel

// tipo de dato void por el momento.
void archivosProcesos(); // representan el espacio de SWAP de cada uno

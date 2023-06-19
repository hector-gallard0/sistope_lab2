#include <stdlib.h>
// Entradas: Archivo de entrada, archivo de salida, número de argumentos, argumentos y el entero 'b'.
// Salidas: Se retorna 1 si se logran abrir los archivos y 0 si ocurre algún error.
// Descripción: Abre los archivos y maneja los errores en caso de que no puedan ser abiertos.
int abrirArchivos(FILE **archivo_entrada, FILE **archivo_salida, int argc, char *argv[], int *n, int *c, int *b);

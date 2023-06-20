#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <getopt.h>
#include <ctype.h>
#include <unistd.h>
// Entradas: Archivo de entrada, archivo de salida, número de argumentos, argumentos y el entero 'b'.
// Salidas: Se retorna 1 si se logran abrir los archivos y 0 si ocurre algún error.
// Descripción: Abre los archivos y maneja los errores en caso de que no puedan ser abiertos.
void abrirArchivos(FILE **archivo_entrada, FILE **archivo_salida, int argc, char *argv[], int *n, int *c, int *b){
    int option;
    while((option = getopt(argc, argv, "i:o:n:c:b")) != -1){
		switch(option){
			case 'i':
				*archivo_entrada = fopen(optarg, "r");
				break;
			case 'o':
				*archivo_salida = fopen(optarg, "w");
				break;
			case 'n':
				*n = atoi(optarg);
				break;
            case 'c':
                *c = atoi(optarg);
                break;
            case 'b':                
                *b = 1;
                break;
            default:
                printf("Faltan parámetros\n\n");
                break;
		}
	}
}
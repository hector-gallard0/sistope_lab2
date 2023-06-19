#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <getopt.h>

// Entradas: Archivo de entrada, archivo de salida, número de argumentos, argumentos y el entero 'b'.
// Salidas: Se retorna 1 si se logran abrir los archivos y 0 si ocurre algún error.
// Descripción: Abre los archivos y maneja los errores en caso de que no puedan ser abiertos.
int abrirArchivos(FILE **archivo_entrada, FILE **archivo_salida, int argc, char *argv[], int *n, int *c, int *b){
    int option;
    while((option = getopt(argc, argv, "i:o:n:c:b")) != -1){
		switch(option){
			case 'i':
				*archivo_entrada = fopen(optarg, "r");

                if(*archivo_entrada == NULL){
                    printf("No se ha podido abrir el archivo de entrada.\n\n");
                    return 0;
                }

				break;
			case 'o':
				*archivo_salida = fopen(optarg, "w");

                if(*archivo_salida == NULL){
                    printf("No se ha podido abrir el archivo de salida.\n\n");
                    return 0;
                }

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
                return 0;
		}
	}

    return 1;
}

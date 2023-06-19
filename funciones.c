#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <getopt.h>
#include <ctype.h>
#include <unistd.h>
// Entradas: Archivo de entrada, archivo de salida, número de argumentos, argumentos y el entero 'b'.
// Salidas: Se retorna 1 si se logran abrir los archivos y 0 si ocurre algún error.
// Descripción: Abre los archivos y maneja los errores en caso de que no puedan ser abiertos.
int abrirArchivos(FILE **archivo_entrada, FILE **archivo_salida, int argc, char *argv[], char **n, char **c, char **b){
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
				*n = optarg;
				break;
            case 'c':
                *c = optarg;
                break;
            case 'b':                
                *b = "1";
                break;
            default:
                printf("Faltan parámetros\n\n");
                return 0;
		}
	}

    return 1;
}

int verificarArchivos(int argc, char *argv[]){
    int option;
    if(argc == 1){
        printf("Faltan argumentos\n");
        return 0;
    }
    while((option = getopt(argc, argv, "i:o:n:c:b")) != -1){
        switch(option){
            case 'i':
                if(fopen(optarg, "r") == NULL){
                    printf("El archivo de entrada no existe.\n\n");
                    return 0;
                }                
                break;
            case 'o':                
                if(fopen(optarg, "w") == NULL){
                    printf("El archivo de salida no existe.\n\n");
                    return 0;
                }                
                break;
            case 'n':
                if(atoi(optarg) < 1){
                    printf("Debe haber al menos 1 worker.\n");
                }
                break;
            case 'c':
                if(atoi(optarg) < 1){
                    printf("El tamaño del chunk debe ser al menos 1.\n");
                }
                break;
            case 'b':         
                                
                break;
            case ':':
                printf("Falta %c", optopt);
                return 0;
                break;
            case '?':
                if (isprint (optopt))
                  printf ("No existe la opcion `-%c'.\n", optopt);              
                return 0;
        }
    }

    return 1;
}

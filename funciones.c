#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <getopt.h>
#include <ctype.h>
#include <unistd.h>

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

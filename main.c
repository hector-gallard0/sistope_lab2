#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "funciones.h"

// Entradas: Número de argumentos (2) y argumentos (-i archivo de entrada, -o salida y -b si se imprime).
// Salidas: Entero, valor de retorno 0. 
// Descripción: Primero se abren los archivos de entrada y salida, luego se lee el archivo de entrada determinando linea a linea si es expresión regular esto, a su vez, leyendo cada caracter. Con cada lectura de linea se actualizan los contadores-
// de expresiones regulares, no regulares y de lineas leidas.
int main(int argc, char *argv[]) {
    FILE *archivo_entrada = NULL, *archivo_salida = NULL;
    int n, c, b = 0;

    if(abrirArchivos(&archivo_entrada, &archivo_salida, argc, argv, &n, &c, &b) == 0){
        return 0;
    }
    else if(archivo_entrada == NULL || archivo_salida == NULL){
        printf("Uno de los archivos no se pudo abrir\n\n");
        return 0;
    }    

    int pid = fork();

    if(pid == 0){
        printf("hijo");
    }else{
        printf("padre");
    }

    fclose(archivo_entrada);
    fclose(archivo_salida);
    return 0;
}
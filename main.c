#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "funciones.h"

// Entradas: Número de argumentos (2) y argumentos (-i archivo de entrada, -o salida y -b si se imprime).
// Salidas: Entero, valor de retorno 0. 
// Descripción: Primero se abren los archivos de entrada y salida, luego se lee el archivo de entrada determinando linea a linea si es expresión regular esto, a su vez, leyendo cada caracter. Con cada lectura de linea se actualizan los contadores-
// de expresiones regulares, no regulares y de lineas leidas.
int main(int argc, char *argv[]) {
    if(verificarArchivos(argc, argv) == 0){
        return 0;
    }

    int pid = fork();

    if(pid == 0){
        execv("./broker", argv);
    }else{       
        printf("padre");
    }
    return 0;
}
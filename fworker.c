#include <stdio.h>

// Entradas: Estado y letra leida.
// Salidas: No hay. 
// Descripción: Dependiendo de la letra leída, se pasa a uno u otro estado, siguiendo el diagrama del AFN del enunciado. Por ejemplo: Si se está en el estado inicial, para pasar al estado 2 se debe leer la letra 'G', cualquier otra letra mantiene el estado en 1 (inicial).
void reconocedor(int *estado, char letra){
    if(*estado == 1){
        if(letra == 'G'){
            *estado = 2;
        }
    }
    else if(*estado == 2){
        if(letra == 'T'){
            *estado = 3;
        }
        else{
           *estado = 1; 
        }
    }
    else if(*estado == 3){
        if(letra == 'C'){
            *estado = 4;
        }
        else if(letra == 'A' || letra == 'G'){
            *estado = 1;
        }
    }
}
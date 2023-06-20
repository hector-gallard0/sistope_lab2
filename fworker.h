#include <stdio.h>

// Entradas: Estado y letra leida.
// Salidas: No hay. 
// Descripción: Dependiendo de la letra leída, se pasa a uno u otro estado, siguiendo el diagrama del AFN del enunciado. Por ejemplo: Si se está en el estado inicial, para pasar al estado 2 se debe leer la letra 'G', cualquier otra letra mantiene el estado en 1 (inicial).
void reconocedor(int *estado, char letra);
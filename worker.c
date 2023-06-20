#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "fworker.h"

int main(){
	LinkedList* resultados = createLinkedList();

	while (1) {
	    char linea[256];
	    int estado = 1;

        if (fgets(linea, sizeof(linea), stdin) == NULL) {
            break; // Terminar el bucle si no se lee ninguna entrada
        }

        if (strcmp(linea, "FIN\n") == 0) {        	
            break;
        }
        
        char caracter;
        for (int i = 0; linea[i] != '\0'; i++) {
            caracter = linea[i];
            reconocedor(&estado, caracter);            
        }        
        // printf("%d / %d / %s", estado, getpid(), linea);

       	char resultado[256] = "";
       	strcat(resultado, linea);    
       	resultado[strlen(resultado) - 1] = '\0';
       	if(estado == 4){
       		strcat(resultado, " SI");       
       	}else{
       		strcat(resultado, " NO");
       	}

        append(resultados, resultado);
        
	}

	printLinkedList(resultados);
	//aca hacer write de cada elemento en la linked list


	freeLinkedList(resultados);
	return 0;
}